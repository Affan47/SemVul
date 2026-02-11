HandleDebugPlaySoundCommand(char* args)
{


    uint32 dwSoundId;
    if (!ExtractUInt32(&args, dwSoundId))
        return false;

    if (!sSoundEntriesStore.LookupEntry(dwSoundId))
    {
        PSendSysMessage(LANG_SOUND_NOT_EXIST, dwSoundId);
        SetSentErrorMessage(true);
        return false;
    }

    Unit* unit = getSelectedUnit();
    if (!unit)
    {
        SendSysMessage(LANG_SELECT_CHAR_OR_CREATURE);
        SetSentErrorMessage(true);
        return false;
    }

    if (m_session->GetPlayer()->GetSelectionGuid())
        unit->PlayDistanceSound(dwSoundId, m_session->GetPlayer());
    else
        unit->PlayDirectSound(dwSoundId, m_session->GetPlayer());

    PSendSysMessage(LANG_YOU_HEAR_SOUND, dwSoundId);
    return true;
}
