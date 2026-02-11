AddToGrid(Corpse* obj, NGridType* grid, Cell const& cell)
{

    if (obj->GetType() != CORPSE_BONES)
    {
        (*grid)(cell.CellX(), cell.CellY()).AddWorldObject(obj);
    }

    else
    {
        (*grid)(cell.CellX(), cell.CellY()).AddGridObject(obj);
    }
}
