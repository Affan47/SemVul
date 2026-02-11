UpdateAI(const uint32 uiDiff) override
    {

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            return;
        }

        if (m_uiTeleportTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_ARCANE_VACUUM) == CAST_OK)
            {
                DoScriptText(SAY_TELEPORT, m_creature);
                m_uiTeleportTimer = 30000;
            }
        }
        else
            { m_uiTeleportTimer -= uiDiff; }


        if (m_uiChillTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_CHILL) == CAST_OK)
            {
                m_uiChillTimer = urand(13000, 25000);
            }
        }
        else
            { m_uiChillTimer -= uiDiff; }


        if (m_uiBreathTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_FROST_BREATH) == CAST_OK)
            {
                m_uiBreathTimer = urand(10000, 15000);
            }
        }
        else
            { m_uiBreathTimer -= uiDiff; }


        if (m_uiManaStormTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_MANA_STORM) == CAST_OK)
                {
                    m_uiManaStormTimer = urand(7500, 12500);
                }
            }
        }
        else
            { m_uiManaStormTimer -= uiDiff; }


        if (m_uiReflectTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_REFLECT) == CAST_OK)
            {
                m_uiReflectTimer = urand(20000, 35000);
            }
        }
        else
            { m_uiReflectTimer -= uiDiff; }


        if (m_uiCleaveTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_CLEAVE) == CAST_OK)
            {
                m_uiCleaveTimer = 7000;
            }
        }
        else
            { m_uiCleaveTimer -= uiDiff; }


        if (!m_bEnraged && m_creature->GetHealthPercent() < 26.0f)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_ENRAGE) == CAST_OK)
            {
                m_bEnraged = true;
            }
        }

        DoMeleeAttackIfReady();
    }
