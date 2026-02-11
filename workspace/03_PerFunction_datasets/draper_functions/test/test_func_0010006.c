JustDied(Unit* ) override
    {
        for (uint8 i = 0; i < 20; ++i)
        {
            m_creature->SummonCreature(NPC_SCARLET_TRAINEE, 1939.18f, -431.58f, 17.09f, 6.22f, TEMPSUMMON_TIMED_OOC_OR_DEAD_DESPAWN, 600000);
        }
    }
