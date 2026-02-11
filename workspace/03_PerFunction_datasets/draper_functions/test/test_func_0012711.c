Update(Map& m, NGridType& grid, GridInfo& info, const uint32& x, const uint32& y, const uint32& t_diff) const
{

    info.UpdateTimeTracker(t_diff);
    if (info.getTimeTracker().Passed())
    {
        if (grid.ActiveObjectsInGrid() == 0 && !m.ActiveObjectsNearGrid(x, y))
        {
            ObjectGridStoper stoper(grid);
            stoper.StopN();
            grid.SetGridState(GRID_STATE_IDLE);
        }
        else
        {
            m.ResetGridExpiry(grid, 0.1f);
        }
    }
}
