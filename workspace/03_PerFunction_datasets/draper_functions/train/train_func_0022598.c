JustRespawned() override
    {

        if (m_bHasEncounterFinished)
        {

            m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);


            debug_log("SD2: boss_majordomo_executus: Relocate to Ragnaros' Lair on respawn");
            m_creature->GetMap()->CreatureRelocation(m_creature, m_aMajordomoLocations[1].m_fX, m_aMajordomoLocations[1].m_fY, m_aMajordomoLocations[1].m_fZ, m_aMajordomoLocations[1].m_fO);
            m_creature->SetActiveObjectState(false);
        }
    }
