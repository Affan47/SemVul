SpellHit(Unit* pUnit, const SpellEntry* pSpell)
{
    for (CreatureEventAIList::iterator i = m_CreatureEventAIList.begin(); i != m_CreatureEventAIList.end(); ++i)
        if ((*i).Event.event_type == EVENT_T_SPELLHIT)

            if (!(*i).Event.spell_hit.spellId || pSpell->Id == (*i).Event.spell_hit.spellId)
                if (pSpell->SchoolMask & (*i).Event.spell_hit.schoolMask)
                    ProcessEvent(*i, pUnit);
}
