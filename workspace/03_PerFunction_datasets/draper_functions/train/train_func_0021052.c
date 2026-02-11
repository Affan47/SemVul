LoadHelper(CellCorpseSet const& cell_corpses, CellPair& cell, CorpseMapType& , uint32& count, Map* map, GridType& grid)
{
    if (cell_corpses.empty())
        { return; }

    for (CellCorpseSet::const_iterator itr = cell_corpses.begin(); itr != cell_corpses.end(); ++itr)
    {
        if (itr->second != map->GetInstanceId())
            { continue; }

        uint32 player_lowguid = itr->first;

        Corpse* obj = sObjectAccessor.GetCorpseForPlayerGUID(ObjectGuid(HIGHGUID_PLAYER, player_lowguid));
        if (!obj)
            { continue; }

        grid.AddWorldObject(obj);

        addUnitState(obj, cell);
        obj->SetMap(map);
        obj->AddToWorld();
        if (obj->isActiveObject())
            { map->AddToActive(obj); }

        ++count;
    }
}
