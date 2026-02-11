HandleAccountCreateCommand(char* args)
{

    char* szAcc = ExtractQuotedOrLiteralArg(&args);
    char* szPassword = ExtractQuotedOrLiteralArg(&args);
    if (!szAcc || !szPassword)
        return false;


    std::string account_name = szAcc;
    std::string password = szPassword;

    AccountOpResult result;
    uint32 expansion = 0;
    if(ExtractUInt32(&args, expansion))
        result = sAccountMgr.CreateAccount(account_name, password, expansion);
    else
        result = sAccountMgr.CreateAccount(account_name, password);
    switch (result)
    {
        case AOR_OK:
            PSendSysMessage(LANG_ACCOUNT_CREATED, account_name.c_str());
            break;
        case AOR_NAME_TOO_LONG:
            SendSysMessage(LANG_ACCOUNT_TOO_LONG);
            SetSentErrorMessage(true);
            return false;
        case AOR_NAME_ALREDY_EXIST:
            SendSysMessage(LANG_ACCOUNT_ALREADY_EXIST);
            SetSentErrorMessage(true);
            return false;
        case AOR_DB_INTERNAL_ERROR:
            PSendSysMessage(LANG_ACCOUNT_NOT_CREATED_SQL_ERROR, account_name.c_str());
            SetSentErrorMessage(true);
            return false;
        default:
            PSendSysMessage(LANG_ACCOUNT_NOT_CREATED, account_name.c_str());
            SetSentErrorMessage(true);
            return false;
    }

    return true;
}
