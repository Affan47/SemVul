UpdateAI(const uint32 uiDiff) override
    {
        if (m_bIsTagged)
        {
            if (m_uiDieTimer < uiDiff)
            {
                m_creature->DealDamage(m_creature, m_creature->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
            }
            else
            {
                m_uiDieTimer -= uiDiff;
            }
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            return;
        }

        DoMeleeAttackIfReady();
    }
