pipe_work(u_int cl)
{
    	DebugLog((ALOG_DPIPE, 0, "pipe_work(%d): %d %d buflen=%d %c", cl,
		  cldata[cl].rfd, cldata[cl].wfd, cldata[cl].buflen,
		  cldata[cl].inbuffer[0]));

	switch (cldata[cl].inbuffer[0])
	    {
	    case 'Y':
		    break;
	    case 'N':
		    cldata[cl].state |= A_DENY;
		    sendto_ircd("K %d %s %u ", cl, cldata[cl].itsip,
				cldata[cl].itsport);
		    break;
#if 0

	    case 'y':

		    cldata[cl].state |= A_RESTRICT;
		    sendto_ircd("k %d %s %u ", cl, cldata[cl].itsip,
				cldata[cl].itsport);
		    break;
#endif
	    default :

		    sendto_log(ALOG_FLOG|ALOG_IRCD, LOG_WARNING,
			       "pipe: unexpected %c for %s[%s]",
			       cldata[cl].inbuffer[0],
			       cldata[cl].host,
			       cldata[cl].itsip);
		    break;
	    }


	close(cldata[cl].rfd);
	cldata[cl].rfd = 0;
	return -1;
}
