HandleServerLogFilterCommand(char* args)
{
    if (!*args)
    {
        SendSysMessage(LANG_LOG_FILTERS_STATE_HEADER);
        for (int i = 0; i < LOG_FILTER_COUNT; ++i)
            if (*logFilterData[i].name)
                { PSendSysMessage("  %-20s = %s", logFilterData[i].name, GetOnOffStr(sLog.HasLogFilter(1 << i))); }
        return true;
    }

    char* filtername = ExtractLiteralArg(&args);
    if (!filtername)
        { return false; }

    bool value;
    if (!ExtractOnOff(&args, value))
    {
        SendSysMessage(LANG_USE_BOL);
        SetSentErrorMessage(true);
        return false;
    }

    if (strncmp(filtername, "all", 4) == 0)
    {
        sLog.SetLogFilter(LogFilters(0xFFFFFFFF), value);
        PSendSysMessage(LANG_ALL_LOG_FILTERS_SET_TO_S, GetOnOffStr(value));
        return true;
    }

    for (int i = 0; i < LOG_FILTER_COUNT; ++i)
    {
        if (!*logFilterData[i].name)
            { continue; }

        if (!strncmp(filtername, logFilterData[i].name, strlen(filtername)))
        {
            sLog.SetLogFilter(LogFilters(1 << i), value);
            PSendSysMessage("  %-20s = %s", logFilterData[i].name, GetOnOffStr(value));
            return true;
        }
    }

    return false;
}
