JustReachedHome() override
    {
        if (!m_pInstance)
        {
            return;
        }

        if (Creature* pOther = GetOtherAdd())
        {
            if (boss_thaddiusAddsAI* pOtherAI = dynamic_cast<boss_thaddiusAddsAI*>(pOther->AI()))
            {
                if (pOtherAI->IsCountingDead())
                {
                    pOther->ForcedDespawn();
                    pOther->Respawn();
                }
            }
        }


        if (!m_creature->HasAura(SPELL_FEUGEN_CHAIN) && !m_creature->HasAura(SPELL_STALAGG_CHAIN))
        {
            JustRespawned();
        }

        m_pInstance->SetData(TYPE_THADDIUS, FAIL);
    }
