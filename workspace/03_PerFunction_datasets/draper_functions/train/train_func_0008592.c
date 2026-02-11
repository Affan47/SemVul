EffectLearnPetSpell(SpellEffectIndex eff_idx)
{
    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        { return; }

    Player* _player = (Player*)m_caster;

    Pet* pet = _player->GetPet();
    if (!pet)
        { return; }
    if (!pet->IsAlive())
        { return; }

    SpellEntry const* learn_spellproto = sSpellStore.LookupEntry(m_spellInfo->EffectTriggerSpell[eff_idx]);
    if (!learn_spellproto)
        { return; }

    pet->SetTP(pet->m_TrainingPoints - pet->GetTPForSpell(learn_spellproto->Id));
    pet->learnSpell(learn_spellproto->Id);

    pet->SavePetToDB(PET_SAVE_AS_CURRENT);
    _player->PetSpellInitialize();

    if (WorldObject const* caster = GetCastingObject())
        { DEBUG_LOG("Spell: %s has learned spell %u from %s", pet->GetGuidStr().c_str(), learn_spellproto->Id, caster->GetGuidStr().c_str()); }
}
