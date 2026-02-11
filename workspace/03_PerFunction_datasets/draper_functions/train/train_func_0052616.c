LearnPetPassives()
{
    CreatureInfo const* cInfo = GetCreatureInfo();
    if (!cInfo)
        { return; }

    CreatureFamilyEntry const* cFamily = sCreatureFamilyStore.LookupEntry(cInfo->Family);
    if (!cFamily)
        { return; }

    PetFamilySpellsStore::const_iterator petStore = sPetFamilySpellsStore.find(cFamily->ID);
    if (petStore != sPetFamilySpellsStore.end())
    {
        for (PetFamilySpellsSet::const_iterator petSet = petStore->second.begin(); petSet != petStore->second.end(); ++petSet)
            { addSpell(*petSet, ACT_DECIDE, PETSPELL_NEW, PETSPELL_FAMILY); }
    }
}
