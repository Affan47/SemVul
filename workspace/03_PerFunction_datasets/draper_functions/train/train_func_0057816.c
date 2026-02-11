JustSummoned(Creature* pSummoned) override
    {
        switch (pSummoned->GetEntry())
        {
            case NPC_EYE_TENTACLE:
                m_lEyeTentaclesList.push_back(pSummoned->GetObjectGuid());

            case NPC_CLAW_TENTACLE:
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                {
                    pSummoned->AI()->AttackStart(pTarget);
                }

                pSummoned->SummonCreature(NPC_TENTACLE_PORTAL, pSummoned->GetPositionX(), pSummoned->GetPositionY(), pSummoned->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                break;
        }
    }
