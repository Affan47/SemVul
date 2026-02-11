HandleLearnAllMyPetTalentsCommand(char* )
{
    Player* player = m_session->GetPlayer();

    Pet* pet = player->GetPet();
    if (!pet)
    {
        SendSysMessage(LANG_NO_PET_FOUND);
        SetSentErrorMessage(true);
        return false;
    }

    CreatureInfo const* ci = pet->GetCreatureInfo();
    if (!ci)
    {
        SendSysMessage(LANG_WRONG_PET_TYPE);
        SetSentErrorMessage(true);
        return false;
    }

    CreatureFamilyEntry const* pet_family = sCreatureFamilyStore.LookupEntry(ci->family);
    if (!pet_family)
    {
        SendSysMessage(LANG_WRONG_PET_TYPE);
        SetSentErrorMessage(true);
        return false;
    }

    if (pet_family->petTalentType < 0)
    {
        SendSysMessage(LANG_WRONG_PET_TYPE);
        SetSentErrorMessage(true);
        return false;
    }

    for (uint32 i = 0; i < sTalentStore.GetNumRows(); ++i)
    {
        TalentEntry const* talentInfo = sTalentStore.LookupEntry(i);
        if (!talentInfo)
            continue;

        TalentTabEntry const* talentTabInfo = sTalentTabStore.LookupEntry(talentInfo->TalentTab);
        if (!talentTabInfo)
            continue;


        if (((1 << pet_family->petTalentType) & talentTabInfo->petTalentMask) == 0)
            continue;


        uint32 spellid = 0;

        for (int rank = MAX_TALENT_RANK - 1; rank >= 0; --rank)
        {
            if (talentInfo->RankID[rank] != 0)
            {
                spellid = talentInfo->RankID[rank];
                break;
            }
        }

        if (!spellid)
            continue;

        SpellEntry const* spellInfo = sSpellStore.LookupEntry(spellid);
        if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo, m_session->GetPlayer(), false))
            continue;


        pet->learnSpellHighRank(spellid);
    }

    player->SendTalentsInfoData(true);

    SendSysMessage(LANG_COMMAND_LEARN_PET_TALENTS);
    return true;
}
