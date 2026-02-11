HandleAHBotReloadCommand(char* )
{
    if (sAuctionBot.ReloadAllConfig())
    {
        SendSysMessage(LANG_AHBOT_RELOAD_OK);
        return true;
    }
    else
    {
        SendSysMessage(LANG_AHBOT_RELOAD_FAIL);
        SetSentErrorMessage(true);
        return false;
    }
}
