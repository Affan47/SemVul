ExtractAccountId(char** args, std::string* accountName , Player** targetIfNullArg )
{
    uint32 account_id = 0;


    char* account_str = ExtractLiteralArg(args);

    if (!account_str)
    {
        if (!targetIfNullArg)
            { return 0; }


        Player* targetPlayer = getSelectedPlayer();
        if (!targetPlayer)
            { return 0; }

        account_id = targetPlayer->GetSession()->GetAccountId();

        if (accountName)
            { sAccountMgr.GetName(account_id, *accountName); }

        if (targetIfNullArg)
            { *targetIfNullArg = targetPlayer; }

        return account_id;
    }

    std::string account_name;

    if (ExtractUInt32(&account_str, account_id))
    {
        if (!sAccountMgr.GetName(account_id, account_name))
        {
            PSendSysMessage(LANG_ACCOUNT_NOT_EXIST, account_str);
            SetSentErrorMessage(true);
            return 0;
        }
    }
    else
    {
        account_name = account_str;
        if (!AccountMgr::normalizeString(account_name))
        {
            PSendSysMessage(LANG_ACCOUNT_NOT_EXIST, account_name.c_str());
            SetSentErrorMessage(true);
            return 0;
        }

        account_id = sAccountMgr.GetId(account_name);
        if (!account_id)
        {
            PSendSysMessage(LANG_ACCOUNT_NOT_EXIST, account_name.c_str());
            SetSentErrorMessage(true);
            return 0;
        }
    }

    if (accountName)
        { *accountName = account_name; }

    if (targetIfNullArg)
        { *targetIfNullArg = NULL; }

    return account_id;
}
