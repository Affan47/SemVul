chap_protrej(int unit)
{
	struct chap_client_state *cs = &client;
	struct chap_server_state *ss = &server;

	if (ss->flags & TIMEOUT_PENDING) {
		ss->flags &= ~TIMEOUT_PENDING;
		UNTIMEOUT(chap_timeout, ss);
	}
	if (ss->flags & AUTH_STARTED) {
		ss->flags = 0;
		auth_peer_fail(0, PPP_CHAP);
	}
	if ((cs->flags & (AUTH_STARTED|AUTH_DONE)) == AUTH_STARTED) {
		cs->flags &= ~AUTH_STARTED;
		error("CHAP authentication failed due to protocol-reject");
		auth_withpeer_fail(0, PPP_CHAP);
	}
}
