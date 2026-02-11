demuxprotrej(unit, protocol)
    int unit;
    u_short protocol;
{
    int i;


    for (i = 0; i < sizeof (prottbl) / sizeof (struct protent); i++)
	if (prottbl[i].protocol == protocol) {
	    (*prottbl[i].protrej)(unit);
	    return;
	}

    syslog(LOG_WARNING,
	   "demuxprotrej: Unrecognized Protocol-Reject for protocol 0x%x",
	   protocol);
}
