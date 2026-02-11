correlate(int sid1, int sid2)
{
    if (sid1 < 0 || sid2 < 0)
        return 0;

    int min = std::min(sid1, sid2), max = std::max(sid1, sid2);
    float correlation = 0;

    try {
        Q q("SELECT weight FROM C.Correlations WHERE x = ? AND y = ?;");
        q << min << max;

        if (q.next())
            q >> correlation;
    }
    WARNIFFAILED();

    return correlation;
}
