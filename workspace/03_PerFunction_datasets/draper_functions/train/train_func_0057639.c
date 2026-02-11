HandleSendMessageCommand(char* args)
{

    Player* rPlayer;
    if (!ExtractPlayerTarget(&args, &rPlayer))
        return false;


    if (!*args)
        return false;


    if (rPlayer->GetSession()->isLogingOut())
    {
        SendSysMessage(LANG_PLAYER_NOT_FOUND);
        SetSentErrorMessage(true);
        return false;
    }


    rPlayer->GetSession()->SendAreaTriggerMessage("%s", args);
    rPlayer->GetSession()->SendAreaTriggerMessage("|cffff0000[Message from administrator]:|r");


    std::string nameLink = GetNameLink(rPlayer);
    PSendSysMessage(LANG_SENDMESSAGE, nameLink.c_str(), args);
    return true;
}
