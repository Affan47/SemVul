setNGrid(NGridType* grid, uint32 x, uint32 y)
{
    if (x >= MAX_NUMBER_OF_GRIDS || y >= MAX_NUMBER_OF_GRIDS)
    {
        sLog.outError("map::setNGrid() Invalid grid coordinates found: %d, %d!", x, y);
        MANGOS_ASSERT(false);
    }
    i_grids[x][y] = grid;
}
