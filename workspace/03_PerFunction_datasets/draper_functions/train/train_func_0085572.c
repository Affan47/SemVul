Unload(const uint32 x, const uint32 y)
{
    MANGOS_ASSERT(x < MAX_NUMBER_OF_GRIDS);
    MANGOS_ASSERT(y < MAX_NUMBER_OF_GRIDS);

    if (m_GridMaps[x][y])
    {

        if (UnrefGrid(x, y) == 0)
        {

        }
    }
}
