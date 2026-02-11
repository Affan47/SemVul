KilledUnit(Unit* pVictim) override
    {

        if (pVictim->GetTypeId() == TYPEID_PLAYER)
        {
            pVictim->CastSpell(pVictim, SPELL_MARK_OF_NATURE_PLAYER, true, NULL, NULL, m_creature->GetObjectGuid());
        }
    }
