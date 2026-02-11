DoSpawnMajordomoIfCan(bool bByPlayerEnter)
{

    if (m_auiEncounter[TYPE_MAJORDOMO] == DONE && m_auiEncounter[TYPE_RAGNAROS] == DONE)
    {
        return;
    }


    if (GetSingleCreatureFromStorage(NPC_MAJORDOMO, true))
    {
        return;
    }


    for (uint8 i = TYPE_MAGMADAR; i < TYPE_MAJORDOMO; ++i)
    {
        if (m_auiEncounter[i] != SPECIAL)
        {
            return;
        }
    }

    Player* pPlayer = GetPlayerInMap();
    if (!pPlayer)
    {
        return;
    }


    uint8 uiSummonPos = m_auiEncounter[TYPE_MAJORDOMO] == DONE ? 1 : 0;
    if (Creature* pMajordomo = pPlayer->SummonCreature(m_aMajordomoLocations[uiSummonPos].m_uiEntry, m_aMajordomoLocations[uiSummonPos].m_fX, m_aMajordomoLocations[uiSummonPos].m_fY, m_aMajordomoLocations[uiSummonPos].m_fZ, m_aMajordomoLocations[uiSummonPos].m_fO, TEMPSUMMON_MANUAL_DESPAWN, 2 * HOUR * IN_MILLISECONDS))
    {
        if (uiSummonPos)
        {
            pMajordomo->SetFactionTemporary(FACTION_MAJORDOMO_FRIENDLY, TEMPFACTION_RESTORE_RESPAWN);
            pMajordomo->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
            pMajordomo->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }
        else
        {
            if (!bByPlayerEnter)
            {
                DoScriptText(SAY_MAJORDOMO_SPAWN, pMajordomo);
            }

            for (uint8 i = 0; i < MAX_MAJORDOMO_ADDS; ++i)
            {
                pMajordomo->SummonCreature(m_aBosspawnLocs[i].m_uiEntry, m_aBosspawnLocs[i].m_fX, m_aBosspawnLocs[i].m_fY, m_aBosspawnLocs[i].m_fZ, m_aBosspawnLocs[i].m_fO, TEMPSUMMON_MANUAL_DESPAWN, DAY * IN_MILLISECONDS);
            }
        }
    }
}
