HandleWhispersCommand(char* args)
{
    if (!*args)
    {
        PSendSysMessage(LANG_COMMAND_WHISPERACCEPTING, GetOnOffStr(m_session->GetPlayer()->isAcceptWhispers()));
        return true;
    }

    bool value;
    if (!ExtractOnOff(&args, value))
    {
        SendSysMessage(LANG_USE_BOL);
        SetSentErrorMessage(true);
        return false;
    }


    if (value)
    {
        m_session->GetPlayer()->SetAcceptWhispers(true);
        SendSysMessage(LANG_COMMAND_WHISPERON);
    }

    else
    {
        m_session->GetPlayer()->SetAcceptWhispers(false);
        SendSysMessage(LANG_COMMAND_WHISPEROFF);
    }

    return true;
}
