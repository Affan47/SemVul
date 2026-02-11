SortListScore(CCGame a, CCGame b)
{
    if (a.GetScore() > b.GetScore())
    {
        return true;
    }
    return false;
}
