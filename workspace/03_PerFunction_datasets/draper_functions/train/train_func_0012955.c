DoDespawnSummons(bool bIsEventEnd = false)
    {
        for (GuidList::const_iterator itr = m_lSummonedGuidList.begin(); itr != m_lSummonedGuidList.end(); ++itr)
        {
            if (Creature* pTemp = m_creature->GetMap()->GetCreature(*itr))
            {
                if (bIsEventEnd && (pTemp->GetEntry() == NPC_INJURED_PEASANT || pTemp->GetEntry() == NPC_PLAGUED_PEASANT))
                {
                    continue;
                }

                pTemp->ForcedDespawn();
            }
        }
    }
