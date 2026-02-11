parseFacility (const tstring& text)
{
    if (text.empty ())
        return fallback_facility;
#ifdef LOG_AUTH
    else if (text == DCMTK_LOG4CPLUS_TEXT ("auth"))
        return LOG_AUTH;
#endif
#ifdef LOG_AUTHPRIV
    else if (text == DCMTK_LOG4CPLUS_TEXT ("authpriv"))
        return LOG_AUTHPRIV;
#endif
#ifdef LOG_CONSOLE
    else if (text == DCMTK_LOG4CPLUS_TEXT ("console"))
        return LOG_CONSOLE;
#endif
#ifdef LOG_CRON
    else if (text == DCMTK_LOG4CPLUS_TEXT ("cron"))
        return LOG_CRON;
#endif
#ifdef LOG_DAEMON
    else if (text == DCMTK_LOG4CPLUS_TEXT ("daemon"))
        return LOG_DAEMON;
#endif
#ifdef LOG_FTP
    else if (text == DCMTK_LOG4CPLUS_TEXT ("ftp"))
        return LOG_FTP;
#endif
#ifdef LOG_KERN
    else if (text == DCMTK_LOG4CPLUS_TEXT ("kern"))
        return LOG_KERN;
#endif
#ifdef LOG_LOCAL0
    else if (text == DCMTK_LOG4CPLUS_TEXT ("local0"))
        return LOG_LOCAL0;
#endif
#ifdef LOG_LOCAL1
    else if (text == DCMTK_LOG4CPLUS_TEXT ("local1"))
        return LOG_LOCAL1;
#endif
#ifdef LOG_LOCAL2
    else if (text == DCMTK_LOG4CPLUS_TEXT ("local2"))
        return LOG_LOCAL2;
#endif
#ifdef LOG_LOCAL3
    else if (text == DCMTK_LOG4CPLUS_TEXT ("local3"))
        return LOG_LOCAL3;
#endif
#ifdef LOG_LOCAL4
    else if (text == DCMTK_LOG4CPLUS_TEXT ("local4"))
        return LOG_LOCAL4;
#endif
#ifdef LOG_LOCAL5
    else if (text == DCMTK_LOG4CPLUS_TEXT ("local5"))
        return LOG_LOCAL5;
#endif
#ifdef LOG_LOCAL6
    else if (text == DCMTK_LOG4CPLUS_TEXT ("local6"))
        return LOG_LOCAL6;
#endif
#ifdef LOG_LOCAL7
    else if (text == DCMTK_LOG4CPLUS_TEXT ("local7"))
        return LOG_LOCAL7;
#endif
#ifdef LOG_LPR
    else if (text == DCMTK_LOG4CPLUS_TEXT ("lpr"))
        return LOG_LPR;
#endif
#ifdef LOG_MAIL
    else if (text == DCMTK_LOG4CPLUS_TEXT ("mail"))
        return LOG_MAIL;
#endif
#ifdef LOG_NEWS
    else if (text == DCMTK_LOG4CPLUS_TEXT ("news"))
        return LOG_NEWS;
#endif
#ifdef LOG_NTP
    else if (text == DCMTK_LOG4CPLUS_TEXT ("ntp"))
        return LOG_NTP;
#endif
#ifdef LOG_SECURITY
    else if (text == DCMTK_LOG4CPLUS_TEXT ("security"))
        return LOG_SECURITY;
#endif
#ifdef LOG_SYSLOG
    else if (text == DCMTK_LOG4CPLUS_TEXT ("syslog"))
        return LOG_SYSLOG;
#endif
#ifdef LOG_USER
    else if (text == DCMTK_LOG4CPLUS_TEXT ("user"))
        return LOG_USER;
#endif
#ifdef LOG_UUCP
    else if (text == DCMTK_LOG4CPLUS_TEXT ("uucp"))
        return LOG_UUCP;
#endif
    else
    {

        tstring msg (DCMTK_LOG4CPLUS_TEXT ("Unknown syslog facility: "));
        msg += text;
        helpers::getLogLog ().error (msg);

        return fallback_facility;
    }
}
