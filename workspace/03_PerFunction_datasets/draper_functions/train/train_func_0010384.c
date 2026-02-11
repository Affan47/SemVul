solve(vector<double> &b) const
{
    int i, j;

    if(b.size() != m.size())
        return false;

    vector<double> bp(b.size());

    for(i = 0; i < (int)b.size(); ++i)
        bp[perm[i]] = b[i];


    for(i = 0; i < (int)bp.size(); ++i) {
        for(j = 0; j < (int)m[i].size(); ++j)
            bp[i] -= bp[m[i][j].first] * m[i][j].second;
        bp[i] /= diag[i];
    }


    for(i = bp.size() - 1; i >= 0; --i) {
        for(j = 0; j < (int)mt[i].size(); ++j)
            bp[i] -= bp[mt[i][j].first] * mt[i][j].second;
        bp[i] /= diag[i];
    }


    for(i = 0; i < (int)b.size(); ++i)
        b[i] = bp[perm[i]];

    return true;
}
