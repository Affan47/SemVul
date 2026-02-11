UpdateAI(const uint32 uiDiff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            return;
        }


        if (m_uiImmolateTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_IMMOLATE) == CAST_OK)
                {
                    m_uiImmolateTimer = urand(5000, 10000);
                }
            }
        }
        else { m_uiImmolateTimer -= uiDiff; }

        if (m_uiSeparationCheckTimer < uiDiff)
        {

            Creature* pGarr = m_pInstance->GetSingleCreatureFromStorage(NPC_GARR);
            if (pGarr && pGarr->IsAlive() && !m_creature->IsWithinDist2d(pGarr->GetPositionX(), pGarr->GetPositionY(), 50.0f))
            {
                DoCastSpellIfCan(m_creature, SPELL_SEPARATION_ANXIETY, CAST_TRIGGERED);
            }

            m_uiSeparationCheckTimer = 5000;
        }
        else
            { m_uiSeparationCheckTimer -= uiDiff; }


        if (m_creature->GetHealthPercent() <= 10.0f)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_ERUPTION);
            m_creature->SetDeathState(JUST_DIED);
            m_creature->RemoveCorpse();
        }

        DoMeleeAttackIfReady();
    }
