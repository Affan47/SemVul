JustDied(Unit* ) override
    {
        DoScriptText(SAY_KORT_DEATH, m_creature);
        DoCastSpellIfCan(m_creature, SPELL_SPIRIT_KORTHAZZ, CAST_TRIGGERED);

        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_FOUR_HORSEMEN, SPECIAL);
        }
    }
