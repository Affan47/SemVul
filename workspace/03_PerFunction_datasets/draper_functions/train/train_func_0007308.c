JustDied(Unit* ) override
    {
        if (m_bIsTagged)
        {
            m_creature->SummonCreature(NPC_FREED_SOUL, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 300000);
        }
    }
