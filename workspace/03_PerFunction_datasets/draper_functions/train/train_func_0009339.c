EffectTameCreature(SpellEffectIndex )
{


    Player* plr = (Player*)GetAffectiveCaster();

    Creature* creatureTarget = (Creature*)unitTarget;


    finish();

    Pet* pet = new Pet(HUNTER_PET);

    if (!pet->CreateBaseAtCreature(creatureTarget))
    {
        delete pet;
        return;
    }

    pet->SetOwnerGuid(plr->GetObjectGuid());
    pet->SetCreatorGuid(plr->GetObjectGuid());
    pet->setFaction(plr->getFaction());
    pet->SetUInt32Value(UNIT_CREATED_BY_SPELL, m_spellInfo->Id);

    if (plr->IsPvP())
        pet->SetPvP(true);

    if (plr->IsFFAPvP())
        pet->SetFFAPvP(true);


    uint32 level = creatureTarget->getLevel() + 5 < plr->getLevel() ? (plr->getLevel() - 5) : creatureTarget->getLevel();

    if (!pet->InitStatsForLevel(level))
    {
        sLog.outError("Pet::InitStatsForLevel() failed for creature (Entry: %u)!", creatureTarget->GetEntry());
        delete pet;
        return;
    }

    pet->GetCharmInfo()->SetPetNumber(sObjectMgr.GeneratePetNumber(), true);

    pet->AIM_Initialize();
    pet->InitPetCreateSpells();
    pet->InitLevelupSpellsForLevel();
    pet->InitTalentForLevel();
    pet->SetHealth(pet->GetMaxHealth());


    creatureTarget->ForcedDespawn();


    pet->SetUInt32Value(UNIT_FIELD_LEVEL, level - 1);


    pet->GetMap()->Add((Creature*)pet);


    pet->SetUInt32Value(UNIT_FIELD_LEVEL, level);


    plr->SetPet(pet);

    pet->SavePetToDB(PET_SAVE_AS_CURRENT);
    plr->PetSpellInitialize();
}
