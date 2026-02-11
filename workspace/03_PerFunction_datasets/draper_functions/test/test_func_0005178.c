update_correlation(int from, int to, float weight)
{
    if (fabs(weight) < 0.25)
        return;

#if defined(DEBUG) && 0
    cerr << " >> Updating link from " << std::min(from, to) << " to "
        << std::max(from, to) << " by " << weight << endl;
#endif

    int min = std::min(from, to), max = std::max(from, to);

    try {
        Q q("INSERT INTO C.Correlations "
                "('x', 'y', 'weight') VALUES (?, ?, ?);");
        q << min << max << weight;
        q.execute();
        return;
    } IGNOREFAILURE();

    {
        Q q("UPDATE C.Correlations SET weight = "
                "max(min(weight + ?, " MAX_CORR_STR "), -" MAX_CORR_STR ") "
                "WHERE x = ? AND y = ?;");
        q << weight << min << max;
        q.execute();
    }
}
