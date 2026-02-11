HandlePetCastSpellOpcode(WorldPacket& recvPacket)
{
    DETAIL_LOG("WORLD: CMSG_PET_CAST_SPELL");

    ObjectGuid guid;
    uint32 spellid;
    uint8  cast_count;
    uint8  unk_flags;

    recvPacket >> guid >> cast_count >> spellid >> unk_flags;

    DEBUG_LOG("WORLD: CMSG_PET_CAST_SPELL, %s, cast_count: %u, spellid %u, unk_flags %u", guid.GetString().c_str(), cast_count, spellid, unk_flags);

    Creature* pet = _player->GetMap()->GetAnyTypeCreature(guid);

    if (!pet || (guid != _player->GetPetGuid() && guid != _player->GetCharmGuid()))
    {
        sLog.outError("HandlePetCastSpellOpcode: %s isn't pet of %s .", guid.GetString().c_str(), GetPlayer()->GetGuidStr().c_str());
        return;
    }

    SpellEntry const* spellInfo = sSpellStore.LookupEntry(spellid);
    if (!spellInfo)
    {
        sLog.outError("WORLD: unknown PET spell id %i", spellid);
        return;
    }

    if (pet->GetCharmInfo() && pet->GetCharmInfo()->GetGlobalCooldownMgr().HasGlobalCooldown(spellInfo))
        return;

    Aura* triggeredByAura = pet->GetTriggeredByClientAura(spellid);


    if ((!triggeredByAura && !pet->HasSpell(spellid)) || IsPassiveSpell(spellInfo))
        return;

    SpellCastTargets targets;

    recvPacket >> targets.ReadForCaster(pet);

    pet->clearUnitState(UNIT_STAT_MOVING);

    Spell* spell = new Spell(pet, spellInfo, triggeredByAura ? true : false, pet->GetObjectGuid(), triggeredByAura ? triggeredByAura->GetSpellProto() : NULL);
    spell->m_cast_count = cast_count;
    spell->m_targets = targets;

    SpellCastResult result = triggeredByAura ? SPELL_CAST_OK : spell->CheckPetCast(NULL);
    if (result == SPELL_CAST_OK)
    {
        pet->AddCreatureSpellCooldown(spellid);
        if (pet->IsPet())
        {


            if (((Pet*)pet)->getPetType() == SUMMON_PET && (urand(0, 100) < 10))
                pet->SendPetTalk((uint32)PET_TALK_SPECIAL_SPELL);
            else
                pet->SendPetAIReaction();
        }

        spell->prepare(&(spell->m_targets), triggeredByAura);
    }
    else
    {
        Unit* owner = pet->GetCharmerOrOwner();
        if (owner && owner->GetTypeId() == TYPEID_PLAYER && !triggeredByAura)
            Spell::SendCastResult((Player*)owner, spellInfo, 0, result, true);

        if (!pet->HasSpellCooldown(spellid) && !triggeredByAura)
            GetPlayer()->SendClearCooldown(spellid, pet);

        spell->finish(false);
        delete spell;
    }
}
