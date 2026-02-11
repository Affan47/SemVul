EnterEvadeMode() override
    {
        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_RAGNAROS, FAIL);
        }


        if (m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
        {
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }

        ScriptedAI::EnterEvadeMode();
    }
