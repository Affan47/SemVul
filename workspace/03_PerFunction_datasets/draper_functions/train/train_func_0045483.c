SpellHit(Unit* pCaster, const SpellEntry* pSpell) override
    {
        if (pCaster->GetTypeId() == TYPEID_PLAYER && m_creature->IsAlive() && pSpell->Id == 20804)
        {
            Player* pPlayer = static_cast<Player*>(pCaster);
            if (pPlayer->GetQuestStatus(6624) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(6622) == QUEST_STATUS_INCOMPLETE)
            {
                if (Creature* pDoctor = m_creature->GetMap()->GetCreature(m_doctorGuid))
                {
                    if (npc_doctorAI* pDocAI = dynamic_cast<npc_doctorAI*>(pDoctor->AI()))
                    {
                        pDocAI->PatientSaved(m_creature, pPlayer, m_pCoord);
                    }
                }
            }

            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);

            m_creature->SetStandState(UNIT_STAND_STATE_STAND);

            switch (urand(0, 2))
            {
                case 0:
                    DoScriptText(SAY_DOC1, m_creature);
                    break;
                case 1:
                    DoScriptText(SAY_DOC2, m_creature);
                    break;
                case 2:
                    DoScriptText(SAY_DOC3, m_creature);
                    break;
            }

            m_creature->SetWalk(false);

            switch (m_creature->GetEntry())
            {
                case 12923:
                case 12924:
                case 12925:
                    m_creature->GetMotionMaster()->MovePoint(0, H_RUNTOX, H_RUNTOY, H_RUNTOZ);
                    break;
                case 12936:
                case 12937:
                case 12938:
                    m_creature->GetMotionMaster()->MovePoint(0, A_RUNTOX, A_RUNTOY, A_RUNTOZ);
                    break;
            }
        }
    }
