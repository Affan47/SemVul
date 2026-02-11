UpdateAI(const uint32 ) override
    {
        if (m_pInstance)
        {
            if (m_pInstance->GetData(TYPE_AYAMISS) == IN_PROGRESS)
            {
                return;
            }
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            return;
        }

        DoMeleeAttackIfReady();
    }
