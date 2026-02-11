WaypointReached(uint32 uiPointId) override
    {
        switch (uiPointId)
        {
            case 11:
                DoScriptText(SAY_STINKY_FIRST_STOP, m_creature);
                break;
            case 17:

                DoScriptText(SAY_STINKY_2_MONSTERS, m_creature);

                if (GameObject* pBogbeanPlant = GetClosestGameObjectWithEntry(m_creature, GO_BOGBEAN_PLANT, DEFAULT_VISIBILITY_DISTANCE))
                {
                    m_bogbeanPlantGuid = pBogbeanPlant->GetObjectGuid();
                    m_creature->SetFacingToObject(pBogbeanPlant);
                }

                break;
            case 19:
                DoScriptText(SAY_STINKY_GATHERING, m_creature);
                break;
            case 24:
                if (Player* pPlayer = GetPlayerForEscort())
                    { pPlayer->GroupEventHappens(pPlayer->GetTeam() == ALLIANCE ? QUEST_ID_STINKYS_ESCAPE_ALLIANCE : QUEST_ID_STINKYS_ESCAPE_HORDE, m_creature); }

                DoScriptText(SAY_STINKY_END, m_creature);
                break;
        }
    }
