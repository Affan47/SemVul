upap_rauthreq(upap_state *u,u_char *inp,int id,int len)
{
	u_char ruserlen, rpasswdlen;
	char *ruser, *rpasswd;
	int retcode;
	char *msg;
	int msglen;

	UPAPDEBUG((LOG_INFO, "upap_rauth: Rcvd id %d.", id));

	if (u->us_serverstate < UPAPSS_LISTEN)
		return;


	if (u->us_serverstate == UPAPSS_OPEN) {
		upap_sresp(u, UPAP_AUTHACK, id, "", 0);
		return;
	}
	if (u->us_serverstate == UPAPSS_BADAUTH) {
		upap_sresp(u, UPAP_AUTHNAK, id, "", 0);
		return;
	}


	if (len < sizeof (u_char)) {
		UPAPDEBUG((LOG_INFO, "upap_rauth: rcvd short packet."));
		return;
	}
	GETCHAR(ruserlen, inp);
	len -= sizeof (u_char) + ruserlen + sizeof (u_char);
	if (len < 0) {
		UPAPDEBUG((LOG_INFO, "upap_rauth: rcvd short packet."));
		return;
	}
	ruser = (char *) inp;
	INCPTR(ruserlen, inp);
	GETCHAR(rpasswdlen, inp);
	if (len < rpasswdlen) {
		UPAPDEBUG((LOG_INFO, "upap_rauth: rcvd short packet."));
		return;
	}
	rpasswd = (char *) inp;


	if(ruserlen > 64)
		ruserlen = 64;
	if(rpasswdlen > 64)
		rpasswdlen = 64;
	strncpy(u->us_ruser,ruser,(int)ruserlen);
	strncpy(u->us_rpasswd,rpasswd,(int)rpasswdlen);
	u->us_rpasswdlen = rpasswdlen;
	u->us_ruserlen = ruserlen;
#ifdef RADIUS
        retcode = radius_check_passwd(u->us_unit, ruser, ruserlen, rpasswd,
                       rpasswdlen, &msg, &msglen);
#else
	retcode = check_passwd(u->us_unit, ruser, ruserlen, rpasswd,
		rpasswdlen, &msg, &msglen);
#endif
	upap_sresp(u, retcode, id, msg, msglen);

	if (retcode == UPAP_AUTHACK) {
		set_userip(ruser, ruserlen);
		u->us_serverstate = UPAPSS_OPEN;
		auth_peer_success(u->us_unit, PPP_PAP);
	} else {
		u->us_serverstate = UPAPSS_BADAUTH;
		auth_peer_fail(u->us_unit, PPP_PAP, AUTH_ERR_USER | AUTH_ERR_PAP);
	}

	if (u->us_reqtimeout > 0)
		UNTIMEOUT(upap_reqtimeout, (caddr_t) u);
}
