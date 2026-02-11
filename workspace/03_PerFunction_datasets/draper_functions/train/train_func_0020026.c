SummonedCreatureJustDied(Creature* pKilled)
    {
        if (pKilled->GetEntry() == NPC_HORDE_DEFENDER)
        {
            --m_uiSummonCountHorde;
            m_uiWaitSummonTimerHorde = 12000;

            m_uiSpawnPosition = 0;
            for (std::list<Creature*>::iterator itrh = lCreatureListHorde.begin(); itrh != lCreatureListHorde.end(); ++itrh, ++m_uiSpawnPosition)
            {
                if ((*itrh) == pKilled)
                {
                    lSpawnListHorde.push_back(m_uiSpawnPosition);
                    (*itrh) = NULL;
                }
            }
            if (m_uiWaitSummonTimerHorde < 1000)
                m_uiWaitSummonTimerHorde = 1000;

            if (urand(0,1))
                DoScriptText(SAY_DEFENDER, m_creature);
        }

        if (pKilled->GetEntry() == NPC_HORDE_AXE_THROWER)
        {
            --m_uiSummonCountHorde;
            m_uiSpawnPosition = 0;
            for (std::list<Creature*>::iterator itrh = lCreatureListHorde.begin(); itrh != lCreatureListHorde.end(); ++itrh, ++m_uiSpawnPosition)
            {
                if ((*itrh) == pKilled)
                {
                    lSpawnListHorde.push_back(m_uiSpawnPosition);
                    (*itrh) = NULL;
                }
            }
            if (m_uiWaitSummonTimerHorde < 1000)
                m_uiWaitSummonTimerHorde = 1000;

            if (urand(0,1))
                DoScriptText(SAY_DEFENDER, m_creature);
        }

        if (pKilled->GetEntry() == NPC_WARLORD_KROMZAR)
        {
            DoScriptText(YELL_RETREAT, m_creature);
            m_uiPhaseCount = 4;
        }

        if (pKilled->GetEntry() == NPC_KOLKAR_INVADER)
        {
            --m_uiSummonCountInvader;
            ++m_uiKillCount;
            m_uiWaitSummonTimer = 10000;

            m_uiSpawnPosition = 0;
            for (std::list<Creature*>::iterator itr = lCreatureList.begin(); itr != lCreatureList.end(); ++itr, ++m_uiSpawnPosition)
            {
                if ((*itr) == pKilled)
                {
                    lSpawnList.push_back(m_uiSpawnPosition);
                    (*itr) = NULL;
                }
            }
        }

        if (pKilled->GetEntry() == NPC_KOLKAR_STORMSEER)
        {
            --m_uiSummonCountStormseer;
            ++m_uiKillCount;
            m_uiWaitSummonTimer = 10000;

            m_uiSpawnPosition = 0;
            for (std::list<Creature*>::iterator itr = lCreatureList.begin(); itr != lCreatureList.end(); ++itr, ++m_uiSpawnPosition)
            {
                if ((*itr) == pKilled)
                {
                    lSpawnList.push_back(m_uiSpawnPosition);
                    (*itr) = NULL;
                }
            }
        }
    }
