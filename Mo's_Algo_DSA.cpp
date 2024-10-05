#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Query {
    int L, R, idx;
};

int BLOCK_SIZE;
vector<int> arr;
vector<int> freq;
vector<int> result;
int current_answer = 0;

void add(int idx) {
    freq[arr[idx]]++;
    if (freq[arr[idx]] == 1) {
        current_answer++;
    }
}

void remove(int idx) {
    if (freq[arr[idx]] == 1) {
        current_answer--;
    }
    freq[arr[idx]]--;
}

bool cmp(const Query &a, const Query &b) {
    if (a.L / BLOCK_SIZE != b.L / BLOCK_SIZE)
        return a.L / BLOCK_SIZE < b.L / BLOCK_SIZE;
    return a.R < b.R;
}

vector<int> mosAlgorithm(int n, vector<Query> &queries) {
    BLOCK_SIZE = sqrt(n);
    result.resize(queries.size());
    freq.assign(100000, 0);
    
    sort(queries.begin(), queries.end(), cmp);
    
    int currL = 0, currR = -1;
    for (Query q : queries) {
        while (currL > q.L) add(--currL);
        while (currR < q.R) add(++currR);
        while (currL < q.L) remove(currL++);
        while (currR > q.R) remove(currR--);
        
        result[q.idx] = current_answer;
    }
    
    return result;
}

int main() {
    int n, q;
    cin >> n >> q;
    arr.resize(n);
    
    for (int i = 0; i < n; ++i) cin >> arr[i];
    
    vector<Query> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].L >> queries[i].R;
        queries[i].idx = i;
    }

    vector<int> ans = mosAlgorithm(n, queries);

    for (int i = 0; i < q; ++i)
