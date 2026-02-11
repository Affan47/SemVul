Reset() override
    {
        if (HasEscortState(STATE_ESCORT_ESCORTING))
        {
            return;
        }

        m_uiBreakKegTimer  = 0;
        m_uiBreakDoorTimer = 0;
    }
