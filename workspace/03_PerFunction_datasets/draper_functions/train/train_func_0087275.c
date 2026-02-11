UpdateAI(const uint32 uiDiff) override
    {

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            return;
        }


        if (m_uiShadowWordPainTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                DoCastSpellIfCan(pTarget, SPELL_SHADOWWORDPAIN);
            }

            m_uiShadowWordPainTimer = 7000;
        }
        else
            { m_uiShadowWordPainTimer -= uiDiff; }


        if (m_uiManaBurnTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0, SPELL_MANABURN, SELECT_FLAG_POWER_MANA))
            {
                DoCastSpellIfCan(pTarget, SPELL_MANABURN);
            }

            m_uiManaBurnTimer = 10000;
        }
        else
            { m_uiManaBurnTimer -= uiDiff; }


        if (m_uiPsychicScreamTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_PSYCHICSCREAM);
            m_uiPsychicScreamTimer = 30000;
        }
        else
            { m_uiPsychicScreamTimer -= uiDiff; }


        if (m_uiShadowShieldTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_SHADOWSHIELD);
            m_uiShadowShieldTimer = 25000;
        }
        else
            { m_uiShadowShieldTimer -= uiDiff; }

        DoMeleeAttackIfReady();
    }
