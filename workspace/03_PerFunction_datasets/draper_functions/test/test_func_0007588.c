HandlePInfoCommand(char* args)
{
    Player* target;
    ObjectGuid target_guid;
    std::string target_name;
    if (!ExtractPlayerTarget(&args, &target, &target_guid, &target_name))
        return false;

    uint32 accId = 0;
    uint32 money = 0;
    uint32 total_player_time = 0;
    uint32 level = 0;
    uint32 latency = 0;


    if (target)
    {

        if (HasLowerSecurity(target))
            return false;

        accId = target->GetSession()->GetAccountId();
        money = target->GetMoney();
        total_player_time = target->GetTotalPlayedTime();
        level = target->getLevel();
        latency = target->GetSession()->GetLatency();
    }

    else
    {

        if (HasLowerSecurity(NULL, target_guid))
            return false;


        QueryResult* result = CharacterDatabase.PQuery("SELECT totaltime, level, money, account FROM characters WHERE guid = '%u'", target_guid.GetCounter());
        if (!result)
            return false;

        Field* fields = result->Fetch();
        total_player_time = fields[0].GetUInt32();
        level = fields[1].GetUInt32();
        money = fields[2].GetUInt32();
        accId = fields[3].GetUInt32();
        delete result;
    }

    std::string username = GetMangosString(LANG_ERROR);
    std::string last_ip = GetMangosString(LANG_ERROR);
    AccountTypes security = SEC_PLAYER;
    std::string last_login = GetMangosString(LANG_ERROR);

    QueryResult* result = LoginDatabase.PQuery("SELECT username,gmlevel,last_ip,last_login FROM account WHERE id = '%u'", accId);
    if (result)
    {
        Field* fields = result->Fetch();
        username = fields[0].GetCppString();
        security = (AccountTypes)fields[1].GetUInt32();

        if (GetAccessLevel() >= security)
        {
            last_ip = fields[2].GetCppString();
            last_login = fields[3].GetCppString();
        }
        else
        {
            last_ip = "-";
            last_login = "-";
        }

        delete result;
    }

    std::string nameLink = playerLink(target_name);

    PSendSysMessage(LANG_PINFO_ACCOUNT, (target ? "" : GetMangosString(LANG_OFFLINE)), nameLink.c_str(), target_guid.GetCounter(), username.c_str(), accId, security, last_ip.c_str(), last_login.c_str(), latency);

    std::string timeStr = secsToTimeString(total_player_time, true, true);
    uint32 gold = money / GOLD;
    uint32 silv = (money % GOLD) / SILVER;
    uint32 copp = (money % GOLD) % SILVER;
    PSendSysMessage(LANG_PINFO_LEVEL,  timeStr.c_str(), level, gold, silv, copp);

    return true;
}
