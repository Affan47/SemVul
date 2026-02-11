HandleInvisibilityDetect(bool apply, bool Real)
{
    Unit* target = GetTarget();

    if (apply)
    {
        target->m_detectInvisibilityMask |= (1 << m_modifier.m_miscvalue);
    }
    else
    {

        target->m_detectInvisibilityMask = 0;
        Unit::AuraList const& auras = target->GetAurasByType(SPELL_AURA_MOD_INVISIBILITY_DETECTION);
        for (Unit::AuraList::const_iterator itr = auras.begin(); itr != auras.end(); ++itr)
            target->m_detectInvisibilityMask |= (1 << (*itr)->GetModifier()->m_miscvalue);
    }
    if (Real && target->GetTypeId() == TYPEID_PLAYER)
        ((Player*)target)->GetCamera().UpdateVisibilityForOwner();
}
