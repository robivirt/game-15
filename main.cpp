#define _GLIBCXX_DEBUG
#include <iostream>
#include <vector>
#include <deque>

const int N = 3;
int move_x[4] = {-1, 0, 0, 1};
int move_y[4] = {0, -1, 1, 0};

int fact(int n) {
    if (n == 0) {
        return 1;
    }
    return n * fact(n - 1);
}

class Field {
public:
    Field() {
        per.resize(N * N);
        pos_i = N - 1;
        pos_j = N - 1;
        for (int i = 0; i < per.size(); i++) {
            per[i] = i + 1;
        }
    }

    Field(const std::vector<std::vector<int>> &arr) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (arr[i][j] == N * N) {
                    pos_i = i;
                    pos_j = j;
                }
                per.push_back(arr[i][j]);
            }
        }
    }

    int& get_cell(int i, int j) {
        return per[i * N + j];
    }

    int get_cell(int i, int j) const {
        return per[i * N + j];
    }

    int& get_last_i() {
        return pos_i;
    }

    int& get_last_j() {
        return pos_j;
    }

    int get_num_per() const {
        int res = 0;
        for (int i = 0; i < per.size(); i++) {
            for (int j = i + 1; j < per.size(); j++) {
                if (per[i] > per[j]) {
                    res += fact(per.size() - i - 1);
                }
            }
        }
        return res;
    }

private:
    std::vector<int> per;
    int pos_i, pos_j;
};

void solve(const std::vector<std::vector<int>> &table) {
    Field field(table);
    std::vector<bool> used(fact(N * N));
    std::vector<Field> pr(fact(N * N));
    used[field.get_num_per()] = true;
    std::deque<Field> dq;    
    dq.push_back(field);
    while (!dq.empty()) {
        Field v = dq.front();
        dq.pop_front();
        for (int type_move = 0; type_move < 4; type_move++) {
            int new_last_i = v.get_last_i() + move_x[type_move];
            int new_last_j = v.get_last_j() + move_y[type_move];
            if (0 <= new_last_i && new_last_i < N && 0 <= new_last_j && new_last_j < N) {
                Field to = v;
                std::swap(to.get_cell(new_last_i, new_last_j), to.get_cell(v.get_last_i(), v.get_last_j()));
                to.get_last_i() = new_last_i;
                to.get_last_j() = new_last_j;
                if (!used[to.get_num_per()]) {
                    used[to.get_num_per()] = true;
                    pr[to.get_num_per()] = v;
                    dq.push_back(to);
                }
            }
        }
    }
    Field last = Field();
    if (used[last.get_num_per()] == false) {
        std::cout << "Solution not found" << std::endl;
        return;
    } else {
        std::cout << "Solution found" << std::endl;
        std::vector<Field> moves;
        while (field.get_num_per() != last.get_num_per()) {
            moves.push_back(last);
            last = pr[last.get_num_per()];
        }
        for (size_t i = 0; i < moves.size(); i++) {
            std::cout << i << "-th move" << std::endl;
            for (int a = 0; a < N; a++) {
                for (int b = 0; b < N; b++) {
                    std::cout << moves[moves.size() - i - 1].get_cell(a, b) << ' ';
                }
                std::cout << std::endl;
            }
        }
        
    }
}

int main() {
    std::vector<std::vector<int>> table(N, std::vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cin >> table[i][j];
        }
    }
    solve(table);
}