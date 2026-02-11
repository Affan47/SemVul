SpellHit(Unit* , const SpellEntry* pSpell) override
    {
        if (HasFollowState(STATE_FOLLOW_INPROGRESS | STATE_FOLLOW_PAUSED) && pSpell->Id == SPELL_REVIVE_RINGO)
        {
            ClearFaint();
        }
    }
