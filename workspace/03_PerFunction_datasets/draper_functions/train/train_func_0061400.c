transitionTimes(const KTimeZone::Phase &phase, const QDateTime &start, const QDateTime &end) const
{
    QList<QDateTime> times;
    int ixstart, ixend;
    if (d->transitionIndexes(start, end, ixstart, ixend))
    {
        if (ixend < 0)
            ixend = d->transitions.count() - 1;
        while (ixstart <= ixend)
        {
            if (d->transitions[ixstart].phase() == phase)
                times += d->transitions[ixstart].time();
        }
    }
    return times;
}
