RemovePersistentState(uint32 mapId, uint32 instanceId)
{
    if (lock_instLists)
        return;

    if (instanceId)
    {
        PersistentStateMap::iterator itr = m_instanceSaveByInstanceId.find(instanceId);
        if (itr != m_instanceSaveByInstanceId.end())
        {

            if (itr->second->GetMapEntry()->IsDungeon())
                if (time_t resettime = ((DungeonPersistentState*)itr->second)->GetResetTimeForDB())
                    CharacterDatabase.PExecute("UPDATE instance SET resettime = '" UI64FMTD "' WHERE id = '%u'", (uint64)resettime, instanceId);

            _ResetSave(m_instanceSaveByInstanceId, itr);
        }
    }
    else
    {
        PersistentStateMap::iterator itr = m_instanceSaveByMapId.find(mapId);
        if (itr != m_instanceSaveByMapId.end())
            _ResetSave(m_instanceSaveByMapId, itr);
    }
}
