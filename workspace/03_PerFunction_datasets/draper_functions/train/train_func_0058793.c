HandleLearnAllMySpellsCommand(char* )
{
    Player* player = m_session->GetPlayer();
    ChrClassesEntry const* clsEntry = sChrClassesStore.LookupEntry(player->getClass());
    if (!clsEntry)
        return true;
    uint32 family = clsEntry->spellfamily;

    for (uint32 i = 0; i < sSkillLineAbilityStore.GetNumRows(); ++i)
    {
        SkillLineAbilityEntry const* entry = sSkillLineAbilityStore.LookupEntry(i);
        if (!entry)
            continue;

        SpellEntry const* spellInfo = sSpellStore.LookupEntry(entry->spellId);
        if (!spellInfo)
            continue;


        if (spellInfo->spellLevel == 0)
            continue;


        if (!player->IsSpellFitByClassAndRace(spellInfo->Id))
            continue;


        if (spellInfo->SpellFamilyName != family)
            continue;


        uint32 first_rank = sSpellMgr.GetFirstSpellInChain(spellInfo->Id);
        if (GetTalentSpellCost(first_rank) > 0)
            continue;


        if (!SpellMgr::IsSpellValid(spellInfo, player, false))
            continue;

        player->learnSpell(spellInfo->Id, false);
    }

    SendSysMessage(LANG_COMMAND_LEARN_CLASS_SPELLS);
    return true;
}
