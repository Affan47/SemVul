WaypointReached(uint32 uiPointId) override
    {
        switch (uiPointId)
        {
            case 0:
                if (GameObject* pCage = m_creature->GetMap()->GetGameObject(m_galensCageGuid))
                {
                    pCage->ResetDoorOrButton();
                }
                break;
            case 20:
                if (Player* pPlayer = GetPlayerForEscort())
                {
                    m_creature->SetFacingToObject(pPlayer);
                    DoScriptText(SAY_QUEST_COMPLETE, m_creature, pPlayer);
                    DoScriptText(EMOTE_WHISPER, m_creature, pPlayer);
                    pPlayer->GroupEventHappens(QUEST_GALENS_ESCAPE, m_creature);
                }
                SetRun(true);
                break;
        }
    }
