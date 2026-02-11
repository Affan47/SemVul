SetDeathState(DeathState s)
{
    Creature::SetDeathState(s);
    if (GetDeathState() == CORPSE)
    {

        if (getPetType() == SUMMON_PET)
            { Unsummon(PET_SAVE_NOT_IN_SLOT); }

        else
        {

            SetUInt32Value(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_NONE);
            RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE);


            MapEntry const* mapEntry = sMapStore.LookupEntry(GetMapId());
            if (!mapEntry || (mapEntry->map_type != MAP_BATTLEGROUND))
                { ModifyPower(POWER_HAPPINESS, -HAPPINESS_LEVEL_SIZE); }

            SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
        }
    }
    else if (GetDeathState() == ALIVE)
    {
        RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
        CastPetAuras(true);
    }
}
