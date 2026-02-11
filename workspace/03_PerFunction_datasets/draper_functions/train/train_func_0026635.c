ChapReceiveFailure(cstate, inp, id, len)
    chap_state *cstate;
    u_char *inp;
    u_char id;
    int len;
{
    u_char msglen;
    u_char *msg;

    CHAPDEBUG((LOG_INFO, "ChapReceiveFailure: Rcvd id %d.", id));

    if (cstate->clientstate != CHAPCS_RESPONSE) {

	CHAPDEBUG((LOG_INFO, "ChapReceiveFailure: in state %d\n",
		   cstate->clientstate));
	return;
    }

    UNTIMEOUT(ChapResponseTimeout, (caddr_t) cstate);


    if (len > 0)
	PRINTMSG(inp, len);

    syslog(LOG_ERR, "CHAP authentication failed");
    auth_withpeer_fail(cstate->unit, PPP_CHAP);
}
