UpdateAI(const uint32 uiDiff) override
    {
        if (m_creature->IsInCombat() && m_creature->getFaction() == FACTION_FRIENDLY)
        {
            EnterEvadeMode();
        }

        ScriptedAI::UpdateAI(uiDiff);
    }
