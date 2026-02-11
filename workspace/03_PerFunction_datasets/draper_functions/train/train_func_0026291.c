ChapReceiveChallenge(cstate, inp, id, len)
    chap_state *cstate;
    u_char *inp;
    int id;
    int len;
{
    int rchallenge_len;
    u_char *rchallenge;
    int secret_len;
    char secret[MAXSECRETLEN];
    char rhostname[256];
    MD5_CTX mdContext;

    CHAPDEBUG((LOG_INFO, "ChapReceiveChallenge: Rcvd id %d.", id));
    if (cstate->clientstate == CHAPCS_CLOSED ||
	cstate->clientstate == CHAPCS_PENDING) {
	CHAPDEBUG((LOG_INFO, "ChapReceiveChallenge: in state %d",
		   cstate->clientstate));
	return;
    }

    if (len < 2) {
	CHAPDEBUG((LOG_INFO, "ChapReceiveChallenge: rcvd short packet."));
	return;
    }

    GETCHAR(rchallenge_len, inp);
    len -= sizeof (u_char) + rchallenge_len;
    if (len < 0) {
	CHAPDEBUG((LOG_INFO, "ChapReceiveChallenge: rcvd short packet."));
	return;
    }
    rchallenge = inp;
    INCPTR(rchallenge_len, inp);

    if (len >= sizeof(rhostname))
	len = sizeof(rhostname) - 1;
    BCOPY(inp, rhostname, len);
    rhostname[len] = '\000';

    CHAPDEBUG((LOG_INFO, "ChapReceiveChallenge: received name field: %s",
	       rhostname));


    if (!get_secret(cstate->unit, cstate->resp_name, rhostname,
		    secret, &secret_len, 0)) {
	secret_len = 0;
	syslog(LOG_WARNING, "No CHAP secret found for authenticating us to %s",
	       rhostname);
    }


    if (cstate->clientstate == CHAPCS_RESPONSE)
	UNTIMEOUT(ChapResponseTimeout, (caddr_t) cstate);

    cstate->resp_id = id;
    cstate->resp_transmits = 0;


    switch (cstate->resp_type) {

    case CHAP_DIGEST_MD5:
	MD5Init(&mdContext);
	MD5Update(&mdContext, &cstate->resp_id, 1);
	MD5Update(&mdContext, secret, secret_len);
	MD5Update(&mdContext, rchallenge, rchallenge_len);
	MD5Final(&mdContext);
	BCOPY(mdContext.digest, cstate->response, MD5_SIGNATURE_SIZE);
	cstate->resp_length = MD5_SIGNATURE_SIZE;
	break;

    default:
	CHAPDEBUG((LOG_INFO, "unknown digest type %d", cstate->resp_type));
	return;
    }

    ChapSendResponse(cstate);
}
