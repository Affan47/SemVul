JustSummoned(Creature* pSummoned) override
    {
        if (pSummoned->GetEntry() != NPC_SPIRESTONE_WARLORD && pSummoned->GetEntry() != NPC_SMOLDERTHORN_BERSERKER)
        {
            return;
        }

        if (m_creature->getVictim())
        {
            Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0);
            pSummoned->AI()->AttackStart(pTarget ? pTarget : m_creature->getVictim());
        }
    }
