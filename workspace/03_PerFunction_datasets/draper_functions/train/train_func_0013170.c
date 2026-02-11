CCcancel(av)
    char	*av[];
{
    ARTDATA	Data;
    STRING	p;

    Data.Posted = Data.Arrived = Now.time;
    Data.Expires = 0;
    Data.Feedsite = "?";
    if ((p = CCgetid(av[0], &Data.MessageID)) != NULL)
	return p;
    if (Mode == OMrunning)
	ARTcancel(&Data, Data.MessageID, TRUE);
    else {

	HISsetup();
	ARTcancel(&Data, Data.MessageID, TRUE);
	HISclose();
    }
#if	defined(DO_LOG_CANCEL_COMMANDS)
    syslog(L_NOTICE, "%s cancelled %s", LogName, Data.MessageID);
#endif
    return NULL;
}
