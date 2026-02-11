HandleHonorAddKillCommand(char* )
{
    Unit* target = getSelectedUnit();
    if (!target)
    {
        SendSysMessage(LANG_PLAYER_NOT_FOUND);
        SetSentErrorMessage(true);
        return false;
    }


    if (target->GetTypeId() == TYPEID_PLAYER && HasLowerSecurity((Player*)target))
        return false;

    m_session->GetPlayer()->RewardHonor(target, 1);
    return true;
}
