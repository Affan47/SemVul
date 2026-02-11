ScriptsProcess()
{
    if (m_scriptSchedule.empty())
        return;


    ScriptScheduleMap::iterator iter = m_scriptSchedule.begin();

    while (!m_scriptSchedule.empty() && (iter->first <= sWorld.GetGameTime()))
    {
        if (iter->second.HandleScriptStep())
        {

            const char* tableName = iter->second.GetTableName();
            uint32 id = iter->second.GetId();
            ObjectGuid sourceGuid = iter->second.GetSourceGuid();
            ObjectGuid targetGuid = iter->second.GetTargetGuid();
            ObjectGuid ownerGuid = iter->second.GetOwnerGuid();

            for (ScriptScheduleMap::iterator rmItr = m_scriptSchedule.begin(); rmItr != m_scriptSchedule.end();)
            {
                if (rmItr->second.IsSameScript(tableName, id, sourceGuid, targetGuid, ownerGuid))
                {
                    m_scriptSchedule.erase(rmItr++);
                    sScriptMgr.DecreaseScheduledScriptCount();
                }
                else
                    ++rmItr;
            }
        }
        else
        {
            m_scriptSchedule.erase(iter);

            sScriptMgr.DecreaseScheduledScriptCount();
        }
        iter = m_scriptSchedule.begin();
    }
}
