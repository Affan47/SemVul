OnFakeingDeath()
    {
        m_uiResurrectTimer = 10000;

        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_THEKAL, SPECIAL);


            if (CanPreventAddsResurrect())
            {
                m_uiResurrectTimer = 1000;
            }
        }
    }
