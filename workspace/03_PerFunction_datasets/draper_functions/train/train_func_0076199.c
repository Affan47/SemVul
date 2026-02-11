initMt()
{
    int i, j;

    mt.clear();
    mt.resize(m.size());

    for(i = 0; i < (int)m.size(); ++i) {
        for(j = 0; j < (int)m[i].size(); ++j) {
            mt[m[i][j].first].push_back(make_pair(i, m[i][j].second));
        }
    }
}
