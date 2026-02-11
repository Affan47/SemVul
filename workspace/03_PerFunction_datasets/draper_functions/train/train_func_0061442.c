MessageDistBroadcast(Player const* player, WorldPacket* msg, float dist, bool to_self, bool own_team_only)
{
    CellPair p = MaNGOS::ComputeCellPair(player->GetPositionX(), player->GetPositionY());

    if (p.x_coord >= TOTAL_NUMBER_OF_CELLS_PER_MAP || p.y_coord >= TOTAL_NUMBER_OF_CELLS_PER_MAP)
    {
        sLog.outError("Map::MessageBroadcast: Player (GUID: %u) have invalid coordinates X:%f Y:%f grid cell [%u:%u]", player->GetGUIDLow(), player->GetPositionX(), player->GetPositionY(), p.x_coord, p.y_coord);
        return;
    }

    Cell cell(p);
    cell.SetNoCreate();

    if (!loaded(GridPair(cell.data.Part.grid_x, cell.data.Part.grid_y)))
        { return; }

    MaNGOS::MessageDistDeliverer post_man(*player, msg, dist, to_self, own_team_only);
    TypeContainerVisitor<MaNGOS::MessageDistDeliverer , WorldTypeMapContainer > message(post_man);
    cell.Visit(p, message, *this, *player, dist);
}
