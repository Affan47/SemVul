SetPosition(uint8 uiPosition, Creature* pLeader)
    {
        m_uiPosition = uiPosition;

        if (!uiPosition)
        {
            m_bIsLeader = true;
        }
        else
        {
            if (pLeader)
            {
                m_leaderGuid = pLeader->GetObjectGuid();
            }
            else
            {
                m_leaderGuid.Clear();
            }
        }

        Reset();
    }
