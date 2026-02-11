JustDied(Unit* ) override
    {
        if (!m_bIsImage)
        {
            DoScriptText(SAY_DEATH, m_creature);

            if (m_pInstance)
            {
                m_pInstance->SetData(TYPE_SKERAM, DONE);
            }
        }

        else
            { m_creature->ForcedDespawn(); }
    }
