HandleModifyHonorCommand(char* args)
{
    if (!*args)
        { return false; }

    Player* target = getSelectedPlayer();
    if (!target)
    {
        SendSysMessage(LANG_PLAYER_NOT_FOUND);
        SetSentErrorMessage(true);
        return false;
    }

    char* field = ExtractLiteralArg(&args);
    if (!field)
        { return false; }

    int32 amount;
    if (!ExtractInt32(&args, amount))
        { return false; }


    if (hasStringAbbr(field, "points"))
    {
        if (amount < 0 || amount > 255)
            { return false; }

        target->SetByteValue(PLAYER_FIELD_BYTES2, 0, amount);
    }
    else if (hasStringAbbr(field, "rank"))
    {
        if (amount < 0 || amount >= HONOR_RANK_COUNT)
            { return false; }
        target->SetByteValue(PLAYER_BYTES_3, 3, amount);
    }
    else if (hasStringAbbr(field, "todaykills"))
        { target->SetUInt16Value(PLAYER_FIELD_SESSION_KILLS, 0, (uint32)amount); }
    else if (hasStringAbbr(field, "yesterdaykills"))
        { target->SetUInt32Value(PLAYER_FIELD_YESTERDAY_KILLS, (uint32)amount); }
    else if (hasStringAbbr(field, "yesterdayhonor"))
        { target->SetUInt32Value(PLAYER_FIELD_YESTERDAY_CONTRIBUTION, (uint32)amount); }
    else if (hasStringAbbr(field, "thisweekkills"))
        { target->SetUInt32Value(PLAYER_FIELD_THIS_WEEK_KILLS, (uint32)amount); }
    else if (hasStringAbbr(field, "thisweekhonor"))
        { target->SetUInt32Value(PLAYER_FIELD_THIS_WEEK_CONTRIBUTION, (uint32)amount); }
    else if (hasStringAbbr(field, "lastweekkills"))
        { target->SetUInt32Value(PLAYER_FIELD_LAST_WEEK_KILLS, (uint32)amount); }
    else if (hasStringAbbr(field, "lastweekhonor"))
        { target->SetUInt32Value(PLAYER_FIELD_LAST_WEEK_CONTRIBUTION, (uint32)amount); }
    else if (hasStringAbbr(field, "lastweekstanding"))
        { target->SetUInt32Value(PLAYER_FIELD_LAST_WEEK_RANK, (uint32)amount); }
    else if (hasStringAbbr(field, "lifetimedishonorablekills"))
        { target->SetUInt32Value(PLAYER_FIELD_LIFETIME_DISHONORABLE_KILLS, (uint32)amount); }
    else if (hasStringAbbr(field, "lifetimehonorablekills"))
        { target->SetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS, (uint32)amount); }

    PSendSysMessage(LANG_COMMAND_MODIFY_HONOR, field, target->GetName(), hasStringAbbr(field, "rank") ? amount : (uint32)amount);

    return true;
}
