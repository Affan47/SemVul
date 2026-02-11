MeetsSelectAttackingRequirement(Unit* pTarget, SpellEntry const* pSpellInfo, uint32 selectFlags) const
{
    if (selectFlags & SELECT_FLAG_PLAYER && pTarget->GetTypeId() != TYPEID_PLAYER)
        { return false; }

    if (selectFlags & SELECT_FLAG_POWER_MANA && pTarget->getPowerType() != POWER_MANA)
        { return false; }
    else if (selectFlags & SELECT_FLAG_POWER_RAGE && pTarget->getPowerType() != POWER_RAGE)
        { return false; }
    else if (selectFlags & SELECT_FLAG_POWER_ENERGY && pTarget->getPowerType() != POWER_ENERGY)
        { return false; }

    if (selectFlags & SELECT_FLAG_IN_MELEE_RANGE && !CanReachWithMeleeAttack(pTarget))
        { return false; }
    if (selectFlags & SELECT_FLAG_NOT_IN_MELEE_RANGE && CanReachWithMeleeAttack(pTarget))
        { return false; }

    if (selectFlags & SELECT_FLAG_IN_LOS && !IsWithinLOSInMap(pTarget))
        { return false; }

    if (pSpellInfo)
    {
        switch (pSpellInfo->rangeIndex)
        {
            case SPELL_RANGE_IDX_SELF_ONLY: return false;
            case SPELL_RANGE_IDX_ANYWHERE:  return true;
            case SPELL_RANGE_IDX_COMBAT:    return CanReachWithMeleeAttack(pTarget);
        }

        SpellRangeEntry const* srange = sSpellRangeStore.LookupEntry(pSpellInfo->rangeIndex);
        float max_range = GetSpellMaxRange(srange);
        float min_range = GetSpellMinRange(srange);
        float dist = GetCombatDistance(pTarget, false);

        return dist < max_range && dist >= min_range;
    }

    return true;
}
