#include <bits/stdc++.h>
using namespace std;

class Placement {
    vector<int> blocks;
    vector<int> processes;
    int last_allocated = 0;

public:
    void init() {
        int n, m;
        cin >> n;
        blocks.resize(n);
        for (int i = 0; i < n; i++) cin >> blocks[i];

        cin >> m;
        processes.resize(m);
        for (int i = 0; i < m; i++) cin >> processes[i];
    }

    void allocate(const string& type) {
        vector<int> allocation(processes.size(), -1);
        vector<int> temp_blocks = blocks;

        for (int i = 0; i < processes.size(); i++) {
            int idx = -1;

            if (type == "First") {
                for (int j = 0; j < temp_blocks.size(); j++) {
                    if (temp_blocks[j] >= processes[i]) {
                        idx = j;
                        break;
                    }
                }
            }

            else if (type == "Best") {
                int min_fit = INT_MAX;
                for (int j = 0; j < temp_blocks.size(); j++) {
                    if (temp_blocks[j] >= processes[i] && temp_blocks[j] < min_fit) {
                        min_fit = temp_blocks[j];
                        idx = j;
                    }
                }
            }

            else if (type == "Worst") {
                int max_fit = -1;
                for (int j = 0; j < temp_blocks.size(); j++) {
                    if (temp_blocks[j] >= processes[i] && temp_blocks[j] > max_fit) {
                        max_fit = temp_blocks[j];
                        idx = j;
                    }
                }
            }

            else if (type == "Next") {
                int n = temp_blocks.size();
                int j = last_allocated;
                int count = 0;
                while (count < n) {
                    if (temp_blocks[j] >= processes[i]) {
                        idx = j;
                        last_allocated = (j + 1) % n;
                        break;
                    }
                    j = (j + 1) % n;
                    count++;
                }
            }

            if (idx != -1) {
                allocation[i] = idx;
                temp_blocks[idx] -= processes[i];
            }
        }

        print(allocation, type);
    }

    void print(vector<int>& allocation, const string& label) {
        cout << "\n" << label << " Fit Allocation:\n";
        cout << "Process\tSize\tBlock\n";
        for (int i = 0; i < processes.size(); i++) {
            cout << "P" << i + 1 << "\t" << processes[i] << "\t";
            if (allocation[i] != -1) cout << allocation[i] + 1 << "\n";
            else cout << "Not Allocated\n";
        }
    }
};

int main() {
    Placement p;
    p.init();
    p.allocate("First");
    p.allocate("Best");
    p.allocate("Worst");
    p.allocate("Next");
    return 0;
}
