UnrefGrid(const uint32& x, const uint32& y)
{
    MANGOS_ASSERT(x < MAX_NUMBER_OF_GRIDS);
    MANGOS_ASSERT(y < MAX_NUMBER_OF_GRIDS);

    int16& iRef = m_GridRef[x][y];

    LOCK_GUARD _lock(m_refMutex);
    if (iRef > 0)
        return (iRef -= 1);

    return 0;
}
