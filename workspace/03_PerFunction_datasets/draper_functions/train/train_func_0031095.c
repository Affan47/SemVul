SetVictim(Unit* pVictim)
    {
        if (pVictim && pVictim->GetTypeId() == TYPEID_PLAYER)
        {


            float fDist = m_creature->GetDistance2d(pVictim);

            uint32 uiEffectMiscValue = 500;
            if (fDist < 25.0f)
            {
                uiEffectMiscValue = 200;
            }
            else if (fDist < 50.0f)
            {
                uiEffectMiscValue = 300;
            }
            else if (fDist < 75.0f)
            {
                uiEffectMiscValue = 400;
            }


            ((Player*)pVictim)->KnockBackFrom(m_creature, -fDist, uiEffectMiscValue * 0.033f);


            m_victimGuid = pVictim->GetObjectGuid();
            m_uiWebWrapTimer = uiEffectMiscValue == 200 ? 1000 : 2000;
        }
    }
