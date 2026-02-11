AttackStart(Unit* pWho) override
    {
        if (!m_bEventMode)
        {
            ScriptedAI::AttackStart(pWho);
        }
    }
