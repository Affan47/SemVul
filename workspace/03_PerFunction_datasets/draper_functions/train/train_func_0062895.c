CanAutoCast(Unit* target)
{
    ObjectGuid targetguid = target->GetObjectGuid();

    for (int j = 0; j < MAX_EFFECT_INDEX; ++j)
    {
        if (m_spellInfo->Effect[j] == SPELL_EFFECT_APPLY_AURA)
        {
            if (m_spellInfo->StackAmount <= 1)
            {
                if (target->HasAura(m_spellInfo->Id, SpellEffectIndex(j)))
                    { return false; }
            }
            else
            {
                if (Aura* aura = target->GetAura(m_spellInfo->Id, SpellEffectIndex(j)))
                    if (aura->GetStackAmount() >= m_spellInfo->StackAmount)
                        { return false; }
            }
        }
        else if (IsAreaAuraEffect(m_spellInfo->Effect[j]))
        {
            if (target->HasAura(m_spellInfo->Id, SpellEffectIndex(j)))
                { return false; }
        }
    }

    SpellCastResult result = CheckPetCast(target);

    if (result == SPELL_CAST_OK || result == SPELL_FAILED_UNIT_NOT_INFRONT)
    {
        FillTargetMap();

        for (TargetList::const_iterator ihit = m_UniqueTargetInfo.begin(); ihit != m_UniqueTargetInfo.end(); ++ihit)
            if (ihit->targetGUID == targetguid)
                { return true; }
    }
    return false;
}
