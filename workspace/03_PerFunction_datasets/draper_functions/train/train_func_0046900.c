GameEventSpawn(int16 event_id)
{
    int32 internal_event_id = mGameEvent.size() + event_id - 1;

    if (internal_event_id < 0 || (size_t)internal_event_id >= mGameEventCreatureGuids.size())
    {
        sLog.outError("GameEventMgr::GameEventSpawn attempt access to out of range mGameEventCreatureGuids element %i (size: " SIZEFMTD ")", internal_event_id, mGameEventCreatureGuids.size());
        return;
    }

    for (GuidList::iterator itr = mGameEventCreatureGuids[internal_event_id].begin(); itr != mGameEventCreatureGuids[internal_event_id].end(); ++itr)
    {

        CreatureData const* data = sObjectMgr.GetCreatureData(*itr);
        if (data)
        {

            if (event_id < 0)
            {
                if (uint16 pool_id = sPoolMgr.IsPartOfAPool<Creature>(*itr))
                {

                    sPoolMgr.SetExcludeObject<Creature>(pool_id, *itr, false);
                    sPoolMgr.UpdatePoolInMaps<Creature>(pool_id);
                    continue;
                }
            }

            sObjectMgr.AddCreatureToGrid(*itr, data);

            Creature::SpawnInMaps(*itr, data);
        }
    }

    if (internal_event_id < 0 || (size_t)internal_event_id >= mGameEventGameobjectGuids.size())
    {
        sLog.outError("GameEventMgr::GameEventSpawn attempt access to out of range mGameEventGameobjectGuids element %i (size: " SIZEFMTD ")", internal_event_id, mGameEventGameobjectGuids.size());
        return;
    }

    for (GuidList::iterator itr = mGameEventGameobjectGuids[internal_event_id].begin(); itr != mGameEventGameobjectGuids[internal_event_id].end(); ++itr)
    {

        GameObjectData const* data = sObjectMgr.GetGOData(*itr);
        if (data)
        {

            if (event_id < 0)
            {
                if (uint16 pool_id = sPoolMgr.IsPartOfAPool<GameObject>(*itr))
                {

                    sPoolMgr.SetExcludeObject<GameObject>(pool_id, *itr, false);
                    sPoolMgr.UpdatePoolInMaps<GameObject>(pool_id);
                    continue;
                }
            }

            sObjectMgr.AddGameobjectToGrid(*itr, data);

            GameObject::SpawnInMaps(*itr, data);
        }
    }

    if (event_id > 0)
    {
        if ((size_t)event_id >= mGameEventSpawnPoolIds.size())
        {
            sLog.outError("GameEventMgr::GameEventSpawn attempt access to out of range mGameEventSpawnPoolIds element %i (size: " SIZEFMTD ")", event_id, mGameEventSpawnPoolIds.size());
            return;
        }

        for (IdList::iterator itr = mGameEventSpawnPoolIds[event_id].begin(); itr != mGameEventSpawnPoolIds[event_id].end(); ++itr)
            sPoolMgr.SpawnPoolInMaps(*itr, true);
    }
}
