Add(Player* player)
{
    player->GetMapRef().link(this, player);
    player->SetMap(this);


    CellPair p = MaNGOS::ComputeCellPair(player->GetPositionX(), player->GetPositionY());
    Cell cell(p);
    EnsureGridLoadedAtEnter(cell, player);
    player->AddToWorld();

    SendInitSelf(player);
    SendInitTransports(player);

    NGridType* grid = getNGrid(cell.GridX(), cell.GridY());
    player->GetViewPoint().Event_AddedToWorld(&(*grid)(cell.CellX(), cell.CellY()));
    UpdateObjectVisibility(player, cell, p);

    if (i_data)
        i_data->OnPlayerEnter(player);

    return true;
}
