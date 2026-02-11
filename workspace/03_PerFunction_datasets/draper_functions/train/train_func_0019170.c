UpdateAI(const uint32 uiDiff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            return;
        }


        if (m_uiArcaneMissilesTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_ARCANE_MISSILES) == CAST_OK)
            {
                m_uiArcaneMissilesTimer = 8000;
            }
        }
        else
            { m_uiArcaneMissilesTimer -= uiDiff; }


        if (m_uiShadowShieldTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_SHADOW_SHIELD) == CAST_OK)
            {
                m_uiShadowShieldTimer = urand(14000, 28000);
            }
        }
        else
            { m_uiShadowShieldTimer -= uiDiff; }


        if (m_uiCurseTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_CURSE) == CAST_OK)
            {
                m_uiCurseTimer = urand(15000, 27000);
            }
        }
        else
            { m_uiCurseTimer -= uiDiff; }


        if (m_creature->GetHealthPercent() > 3.0f)
        {
            if (m_uiTeleportTimer < uiDiff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0, SPELL_SHADOW_PORTAL, SELECT_FLAG_PLAYER))
                {
                    if (DoCastSpellIfCan(pTarget, SPELL_SHADOW_PORTAL) == CAST_OK)
                    {

                        if (m_creature->GetThreatManager().getThreat(pTarget))
                        {
                            m_creature->GetThreatManager().modifyThreatPercent(pTarget, -100);
                        }

                        m_uiTeleportTimer = urand(20000, 35000);
                    }
                }
            }
            else
            {
                m_uiTeleportTimer -= uiDiff;
            }
        }

        DoMeleeAttackIfReady();
    }
