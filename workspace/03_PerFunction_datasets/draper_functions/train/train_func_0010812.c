UpdateAI(const uint32 uiDiff) override
    {
        DialogueUpdate(uiDiff);

        if (m_uiEventTimer)
        {
            if (m_uiEventTimer <= uiDiff)
            {
                switch (m_uiEventStage)
                {
                    case 0:

                        StartNextDialogueText(NPC_ANACHRONOS_THE_ANCIENT);
                        m_uiEventTimer = 0;
                        break;
                    case 1:

                        m_creature->GetMotionMaster()->MovePoint(POINT_ID_SCEPTER_2, aEternalBoardMovement[6].m_fX, aEternalBoardMovement[6].m_fY, aEternalBoardMovement[6].m_fZ);
                        m_creature->SetStandState(UNIT_STAND_STATE_STAND);
                        m_uiEventTimer = 0;
                        break;
                    case 2:

                        if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_playerGuid))
                        {
                            pPlayer->GroupEventHappens(QUEST_A_PAWN_ON_THE_ETERNAL_BOARD, m_creature);
                        }
                        m_creature->SetStandState(UNIT_STAND_STATE_STAND);
                        m_uiEventTimer = 4000;
                        break;
                    case 3:

                        m_creature->SetWalk(false);
                        m_creature->GetMotionMaster()->MovePoint(POINT_ID_EXIT, aEternalBoardMovement[8].m_fX, aEternalBoardMovement[8].m_fY, aEternalBoardMovement[8].m_fZ);
                        m_uiEventTimer = 0;
                        break;
                    case 4:

                        m_creature->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND);
                        m_creature->SetLevitate(true);
                        m_creature->GetMotionMaster()->MovePoint(0, aEternalBoardMovement[9].m_fX, aEternalBoardMovement[9].m_fY, aEternalBoardMovement[9].m_fZ);
                        m_creature->ForcedDespawn(10000);
                        m_uiEventTimer = 0;
                        break;
                }
                ++m_uiEventStage;
            }
            else
            {
                m_uiEventTimer -= uiDiff;
            }
        }
    }
