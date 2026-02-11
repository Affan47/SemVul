DoSpawnBandits(int uiAmbushId)
    {
        for (int i = 0; i < 2; ++i)
            m_creature->SummonCreature(NPC_GRIM_BANDIT,
                                       m_afBanditLoc[i + uiAmbushId][0], m_afBanditLoc[i + uiAmbushId][1], m_afBanditLoc[i + uiAmbushId][2], 0.0f,
                                       TEMPSUMMON_TIMED_OOC_OR_DEAD_DESPAWN, 60000);
    }
