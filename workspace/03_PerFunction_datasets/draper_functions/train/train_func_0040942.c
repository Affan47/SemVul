CheckUnusedAISummons()
{
    std::set<int32> idx_set;

    for (CreatureEventAI_Summon_Map::const_iterator itr = m_CreatureEventAI_Summon_Map.begin(); itr != m_CreatureEventAI_Summon_Map.end(); ++itr)
        idx_set.insert(itr->first);

    for (CreatureEventAI_Event_Map::const_iterator itr = m_CreatureEventAI_Event_Map.begin(); itr != m_CreatureEventAI_Event_Map.end(); ++itr)
    {
        for (size_t i = 0; i < itr->second.size(); ++i)
        {
            CreatureEventAI_Event const& event = itr->second[i];

            for (int j = 0; j < MAX_ACTIONS; ++j)
            {
                CreatureEventAI_Action const& action = event.action[j];
                switch (action.type)
                {
                    case ACTION_T_SUMMON_ID:
                    {
                        if (action.summon_id.spawnId)
                            idx_set.erase(action.summon_id.spawnId);
                        break;
                    }
                    default: break;
                }
            }
        }
    }

    for (std::set<int32>::const_iterator itr = idx_set.begin(); itr != idx_set.end(); ++itr)
        sLog.outErrorEventAI("Entry %i in table `creature_ai_summons` but not used in EventAI scripts.", *itr);
}
