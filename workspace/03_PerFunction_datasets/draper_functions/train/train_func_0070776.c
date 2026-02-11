GetGothSummonPointCreatures(std::list<Creature*>& lList, bool bRightSide)
{
    for (UNORDERED_MAP<ObjectGuid, GothTrigger>::iterator itr = m_mGothTriggerMap.begin(); itr != m_mGothTriggerMap.end(); ++itr)
    {
        if (itr->second.bIsAnchorHigh)
        {
            continue;
        }

        if (itr->second.bIsRightSide != bRightSide)
        {
            continue;
        }

        if (Creature* pCreature = instance->GetCreature(itr->first))
        {
            lList.push_back(pCreature);
        }
    }
}
