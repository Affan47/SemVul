GetWeaponAttackType(SpellEntry const* spellInfo)
{
    if (!spellInfo)
        { return BASE_ATTACK; }

    switch (spellInfo->DmgClass)
    {
        case SPELL_DAMAGE_CLASS_MELEE:
            if (spellInfo->HasAttribute(SPELL_ATTR_EX3_REQ_OFFHAND))
                { return OFF_ATTACK; }
            else
                { return BASE_ATTACK; }
            break;
        case SPELL_DAMAGE_CLASS_RANGED:
            return RANGED_ATTACK;
            break;
        default:

            if (spellInfo->HasAttribute(SPELL_ATTR_EX2_AUTOREPEAT_FLAG))
                { return RANGED_ATTACK; }
            else
                { return BASE_ATTACK; }
            break;
    }
}
