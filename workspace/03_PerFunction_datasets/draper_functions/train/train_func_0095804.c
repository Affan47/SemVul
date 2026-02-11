Reset() override
    {
        boss_emerald_dragonAI::Reset();

        m_uiArcaneBlastTimer = 12000;
        m_uiBellowingRoarTimer = 30000;
        m_uiShadesTimeoutTimer = 0;
        m_uiShadesDead = 0;


        if (m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
        {
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }
    }
