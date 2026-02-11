SummonedCreatureDespawn(Creature* pSummoned) override
    {

        if (SelectHostileTarget())
        {
            return;
        }


        if (Creature* pPortal = GetClosestCreatureWithEntry(pSummoned, NPC_TENTACLE_PORTAL, 5.0f))
        {
            pPortal->ForcedDespawn();
        }
    }
