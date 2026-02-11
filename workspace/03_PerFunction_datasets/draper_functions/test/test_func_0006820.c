UpdateEscortAI(const uint32 uiDiff) override
    {
        DialogueUpdate(uiDiff);


        if (m_uiGuardCheckTimer)
        {
            if (m_uiGuardCheckTimer <= uiDiff)
            {
                uint8 uiDeadGuardsCount = 0;
                for (GuidList::const_iterator itr = m_lRoyalGuardsGuidList.begin(); itr != m_lRoyalGuardsGuidList.end(); ++itr)
                {
                    if (Creature* pGuard = m_creature->GetMap()->GetCreature(*itr))
                    {
                        if (!pGuard->IsAlive() && pGuard->GetEntry() == NPC_GUARD_ONYXIA)
                        {
                            ++uiDeadGuardsCount;
                        }
                    }
                }
                if (uiDeadGuardsCount == m_lRoyalGuardsGuidList.size())
                {
                    StartNextDialogueText(NPC_GUARD_ONYXIA);
                    m_uiGuardCheckTimer = 0;
                }
                else
                {
                    m_uiGuardCheckTimer = 1000;
                }
            }
            else
            {
                m_uiGuardCheckTimer -= uiDiff;
            }
        }
    }
