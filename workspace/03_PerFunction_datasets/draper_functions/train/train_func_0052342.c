SpellHit(Unit* , const SpellEntry* pSpell) override
    {
        if (!m_bIsTagged && pSpell->Id == SPELL_EGAN_BLASTER)
        {
            m_bIsTagged = true;
        }
    }
