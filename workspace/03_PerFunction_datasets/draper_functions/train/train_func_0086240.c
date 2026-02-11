HandleModifyTalentCommand(char* args)
{
    if (!*args)
        return false;

    int tp = atoi(args);
    if (tp < 0)
        return false;

    Unit* target = getSelectedUnit();
    if (!target)
    {
        SendSysMessage(LANG_NO_CHAR_SELECTED);
        SetSentErrorMessage(true);
        return false;
    }

    if (target->GetTypeId() == TYPEID_PLAYER)
    {

        if (HasLowerSecurity((Player*)target))
            return false;

        ((Player*)target)->SetFreeTalentPoints(tp);
        ((Player*)target)->SendTalentsInfoData(false);
        return true;
    }
    else if (((Creature*)target)->IsPet())
    {
        Unit* owner = target->GetOwner();
        if (owner && owner->GetTypeId() == TYPEID_PLAYER && ((Pet*)target)->IsPermanentPetFor((Player*)owner))
        {

            if (HasLowerSecurity((Player*)owner))
                return false;

            ((Pet*)target)->SetFreeTalentPoints(tp);
            ((Player*)owner)->SendTalentsInfoData(true);
            return true;
        }
    }

    SendSysMessage(LANG_NO_CHAR_SELECTED);
    SetSentErrorMessage(true);
    return false;
}
