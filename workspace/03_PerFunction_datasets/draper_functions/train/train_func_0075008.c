JustSummoned(Creature* pSummoned) override
    {

        if (pSummoned->GetEntry() == NPC_BURU_EGG_TRIGGER)
        {
            pSummoned->CastSpell(pSummoned, SPELL_BURU_EGG_TRIGGER, true);
        }

        else if (pSummoned->GetEntry() == NPC_HATCHLING)
        {
            if (m_pInstance)
            {
                if (Creature* pBuru = m_pInstance->GetSingleCreatureFromStorage(NPC_BURU))
                {
                    if (Unit* pTarget = pBuru->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                    {
                        pSummoned->AI()->AttackStart(pTarget);
                    }
                }
            }
        }
    }
