SummonedCreatureJustDied(Creature* pSummoned) override
    {
        switch (pSummoned->GetEntry())
        {
            case NPC_GUARDIAN:
            case NPC_SOLDIER_FROZEN:
            case NPC_SOUL_WEAVER:
                m_lAddsSet.erase(pSummoned->GetObjectGuid());
                break;
            case NPC_UNSTOPPABLE_ABOM:
                m_lAddsSet.erase(pSummoned->GetObjectGuid());
                break;
        }
    }
