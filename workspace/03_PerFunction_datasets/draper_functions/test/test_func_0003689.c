MoveInLineOfSight(Unit* pWho) override
    {
        if (pWho->GetEntry() == NPC_SMEED)
        {
            if (m_creature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP))
            {
                return;
            }

            if (m_creature->IsWithinDistInMap(pWho, 10.0f))
            {
                switch (urand(0, 2))
                {
                    case 0:
                        DoScriptText(SAY_SMEED_HOME_1, pWho);
                        break;
                    case 1:
                        DoScriptText(SAY_SMEED_HOME_2, pWho);
                        break;
                    case 2:
                        DoScriptText(SAY_SMEED_HOME_3, pWho);
                        break;
                }


                m_creature->CastSpell(m_creature, SPELL_KODO_KOMBO_GOSSIP, true);
            }
        }
    }
