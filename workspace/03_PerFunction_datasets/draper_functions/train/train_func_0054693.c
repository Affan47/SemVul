Reset() override
    {
        if (!HasEscortState(STATE_ESCORT_ESCORTING))
        {
            m_uiCreaturesCount  = 0;
            m_bIsAttacked       = false;
        }
    }
