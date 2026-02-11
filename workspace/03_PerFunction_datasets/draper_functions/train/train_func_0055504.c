AttackedBy(Unit* pAttacker) override
    {
        if (!m_bIsFirstHit)
        {
            if (pAttacker->GetEntry() == NPC_MUTANUS)
            {
                DoScriptText(SAY_MUTANUS, m_creature, pAttacker);
            }

            else if (m_uiPoint >= 30)
            {
                DoScriptText(SAY_AGGRO_3, m_creature, pAttacker);
            }
            else

            {
                DoScriptText(roll_chance_i(90) ? SAY_AGGRO_1 : SAY_AGGRO_2, m_creature, pAttacker);
            }

            m_bIsFirstHit = true;
        }
    }
