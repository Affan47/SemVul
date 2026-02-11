HandleAuraStopNaturalManaRegen(bool apply, bool Real)
{
    if (!Real)
        return;

    GetTarget()->ApplyModFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_REGENERATE_POWER, !apply && !GetTarget()->IsUnderLastManaUseEffect());
}
