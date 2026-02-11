WaypointReached(uint32 i) override
    {
        Player* pPlayer = GetPlayerForEscort();

        if (!pPlayer)
        {
            return;
        }

        switch (i)
        {

            case 22:
                DoScriptText(SAY_OOX_AMBUSH, m_creature);
                m_creature->SummonCreature(NPC_SCORPION, -8340.70f, -4448.17f, 9.17f, 3.10f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000);
                m_creature->SummonCreature(NPC_SCORPION, -8343.18f, -4444.35f, 9.44f, 2.35f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000);
                m_creature->SummonCreature(NPC_SCORPION, -8348.70f, -4457.80f, 9.58f, 2.02f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000);
                break;

            case 28:
                DoScriptText(SAY_OOX_AMBUSH, m_creature);

                m_creature->SummonCreature(NPC_SCOFFLAW, -7488.02f, -4786.56f, 10.67f, 3.74f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
                m_creature->SummonCreature(NPC_SHADOW_MAGE, -7486.41f, -4791.55f, 10.54f, 3.26f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000);

                if (Creature* pCreature = m_creature->SummonCreature(NPC_SCOFFLAW, -7488.47f, -4800.77f, 9.77f, 2.50f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000))
                {
                    DoScriptText(SAY_OOX17_AMBUSH_REPLY, pCreature);
                }

                break;
            case 34:
                DoScriptText(SAY_OOX_END, m_creature);

                pPlayer->GroupEventHappens(QUEST_RESCUE_OOX_17TN, m_creature);
                break;
        }
    }
