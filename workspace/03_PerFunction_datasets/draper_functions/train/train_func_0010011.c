Aggro(Unit* ) override
    {
        switch (urand(0, 2))
        {
            case 0:
                DoScriptText(SAY_AGGRO_1, m_creature);
                break;
            case 1:
                DoScriptText(SAY_AGGRO_2, m_creature);
                break;
            case 2:
                DoScriptText(SAY_AGGRO_3, m_creature);
                break;
        }


        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }
