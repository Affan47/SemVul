NCpostit(cp)
    register CHANNEL	*cp;
{
    STRING		response;
    WIP			*wp;


    switch (Mode) {
    default:
	syslog(L_ERROR, "%s internal NCpostit mode %d", CHANname(cp), Mode);
	return;
    case OMpaused:
	SCHANadd(cp, (time_t)(Now.time + PAUSE_RETRY_TIME), (POINTER)&Mode,
	    NCpostit, (POINTER)NULL);
	return;
    case OMrunning:
	wp = &NCwip[cp->fd];
	response = ARTpost(cp, AmSlave ? &wp->Replic : NULL, wp->MessageID);
	if (atoi(response) == NNTP_TOOKIT_VAL) {
	    cp->Received++;
	    if (cp->Sendid.Size > 3) {
		char buff[4];
		(void)sprintf(buff, "%d", NNTP_OK_RECID_VAL);
		cp->Sendid.Data[0] = buff[0];
		cp->Sendid.Data[1] = buff[1];
		cp->Sendid.Data[2] = buff[2];
		response = cp->Sendid.Data;
	    }
	} else {
            cp->Rejected++;
	    if (cp->Sendid.Size) response = cp->Sendid.Data;
        }
	cp->Reported++;
	if (cp->Reported >= NNTP_ACTIVITY_SYNC) {
	    syslog(L_NOTICE,
	    "%s checkpoint seconds %ld accepted %ld refused %ld rejected %ld",
		CHANname(cp), (long)(Now.time - cp->Started),
		cp->Received, cp->Refused, cp->Rejected);
	    cp->Reported = 0;
	}
	cp->State = CSgetcmd;
	NCwritereply(cp, response);
#ifdef NCPRECOM_PEDANTIC
        NCprecomval = dbzhash(wp->MessageID, strlen(wp->MessageID));
        NCprecompos = NCprecomval % NCPRECOMCACHESIZE;
        NCprecomcache[NCprecompos].MessageIDHash = 0L;
#endif
	break;

    case OMthrottled:
	NCwriteshutdown(cp, ModeReason);
	cp->Rejected++;
	break;
    }


    NCclearwip(&NCwip[cp->fd]);
}
