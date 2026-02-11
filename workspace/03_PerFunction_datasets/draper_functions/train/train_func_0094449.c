_ResetInstance(uint32 mapid, uint32 instanceId)
{
    DEBUG_LOG("MapPersistentStateManager::_ResetInstance %u, %u", mapid, instanceId);

    PersistentStateMap::iterator itr = m_instanceSaveByInstanceId.find(instanceId);
    if (itr != m_instanceSaveByInstanceId.end())
    {

        if (Map* iMap = itr->second->GetMap())
        {
            MANGOS_ASSERT(iMap->IsDungeon());

            ((DungeonMap*)iMap)->Reset(INSTANCE_RESET_RESPAWN_DELAY);
            return;
        }

        _ResetSave(m_instanceSaveByInstanceId, itr);
    }


    DeleteInstanceFromDB(instanceId);
}
