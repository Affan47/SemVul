SITEflushcheck(SITE *sp, struct buffer *bp)
{
    int	                i;
    CHANNEL	        *cp;


    if (sp->Buffered) {
	if (bp->left < sp->Flushpoint)
	    return;
	while (SITEcount >= MaxOutgoing)
	    SITEbufferoldest();
	if (!SITEsetup(sp) || sp->Buffered) {
	    syslog(L_ERROR, "%s cant unbuffer %m", sp->Name);
	    return;
	}
	WCHANsetfrombuffer(sp->Channel, bp);
	WCHANadd(sp->Channel);

	buffer_set(bp, "", 0);
    }

    if (PROCneedscan)
	PROCscan();


    cp = sp->Channel;
    i = cp->Out.left;
    if (i < sp->StopWriting)
	WCHANremove(cp);
    if ((sp->StartWriting == 0 || i > sp->StartWriting)
     && !CHANsleeping(cp)) {
	if (sp->Type == FTchannel) {
	    int j;
	    if (bp->left == 0)
		return;
	    j = write(cp->fd, &bp->data[bp->used], bp->left);
	    if (j > 0) {
		bp->left -= j;
		bp->used += j;
		i = cp->Out.left;


		cp->BadWrites = 0;
		cp->BlockedWrites = 0;
	    }
	    if (bp->left <= 0) {


                bp->used = bp->left = 0;
		WCHANremove(cp);
            } else
		WCHANadd(cp);
	}
	else
	    WCHANadd(cp);
    }

    cp->LastActive = Now.tv_sec;


    if (sp->Type == FTfile || sp->StartSpooling == 0 || i < sp->StartSpooling)
	return;

    syslog(L_ERROR, "%s spooling %d bytes", sp->Name, i);
    if(!SITECHANbilge(sp)) {
	syslog(L_ERROR, "%s overflow %d bytes", sp->Name, i);
	return;
    }
}
