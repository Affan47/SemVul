ReputationToRank(int32 standing)
{
    int32 limit = Reputation_Cap + 1;
    for (int i = MAX_REPUTATION_RANK - 1; i >= MIN_REPUTATION_RANK; --i)
    {
        limit -= PointsInRank[i];
        if (standing >= limit)
            { return ReputationRank(i); }
    }
    return MIN_REPUTATION_RANK;
}
