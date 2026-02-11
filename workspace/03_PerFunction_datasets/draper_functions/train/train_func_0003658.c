JustSummoned(Creature* pSummoned) override
    {

        if (Player* pPlayer = GetPlayerForEscort())
        {
            pSummoned->AI()->AttackStart(pPlayer);
        }
    }
