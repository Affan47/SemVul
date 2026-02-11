JustDied(Unit* pKiller) override
    {
        if (pKiller->GetTypeId() == TYPEID_UNIT && pKiller->GetEntry() == NPC_RAGNAROS)
        {
            DoScriptText(SAY_ARRIVAL4_MAJ, m_creature);
        }
    }
