CreateBaseAtCreature(Creature* creature)
{
    if (!creature)
    {
        sLog.outError("CRITICAL: NULL pointer passed into CreateBaseAtCreature()");
        return false;
    }

    CreatureCreatePos pos(creature, creature->GetOrientation());

    uint32 guid = creature->GetMap()->GenerateLocalLowGuid(HIGHGUID_PET);

    BASIC_LOG("Create pet");
    uint32 pet_number = sObjectMgr.GeneratePetNumber();
    if (!Create(guid, pos, creature->GetCreatureInfo(), pet_number))
        { return false; }

    CreatureInfo const* cinfo = GetCreatureInfo();
    if (!cinfo)
    {
        sLog.outError("CreateBaseAtCreature() failed, creatureInfo is missing!");
        return false;
    }

    if (cinfo->CreatureType == CREATURE_TYPE_CRITTER)
    {
        setPetType(MINI_PET);
        return true;
    }
    SetDisplayId(creature->GetDisplayId());
    SetNativeDisplayId(creature->GetNativeDisplayId());
    SetMaxPower(POWER_HAPPINESS, GetCreatePowers(POWER_HAPPINESS));
    SetPower(POWER_HAPPINESS, 166500);
    setPowerType(POWER_FOCUS);
    SetUInt32Value(UNIT_FIELD_PET_NAME_TIMESTAMP, 0);
    SetUInt32Value(UNIT_FIELD_PETEXPERIENCE, 0);
    SetUInt32Value(UNIT_FIELD_PETNEXTLEVELEXP, sObjectMgr.GetXPForPetLevel(creature->getLevel()));
    SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_NONE);

    if (CreatureFamilyEntry const* cFamily = sCreatureFamilyStore.LookupEntry(cinfo->Family))
        { SetName(cFamily->Name[sWorld.GetDefaultDbcLocale()]); }
    else
        { SetName(creature->GetNameForLocaleIdx(sObjectMgr.GetDBCLocaleIndex())); }

    m_loyaltyPoints = 1000;
    if (cinfo->CreatureType == CREATURE_TYPE_BEAST)
    {
        SetByteValue(UNIT_FIELD_BYTES_0, 1, CLASS_WARRIOR);
        SetByteValue(UNIT_FIELD_BYTES_0, 2, GENDER_NONE);
        SetByteValue(UNIT_FIELD_BYTES_0, 3, POWER_FOCUS);
        SetSheath(SHEATH_STATE_MELEE);
        SetByteValue(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_UNK3 | UNIT_BYTE2_FLAG_AURAS | UNIT_BYTE2_FLAG_UNK5);
        SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_PVP_ATTACKABLE | UNIT_FLAG_RESTING | UNIT_FLAG_RENAME);

        SetUInt32Value(UNIT_MOD_CAST_SPEED, creature->GetUInt32Value(UNIT_MOD_CAST_SPEED));
        SetLoyaltyLevel(REBELLIOUS);
    }
    return true;
}
