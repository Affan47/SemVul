chap_lowerdown(int unit)
{
	struct chap_client_state *cs = &client;
	struct chap_server_state *ss = &server;

	cs->flags = 0;
	if (ss->flags & TIMEOUT_PENDING)
		UNTIMEOUT(chap_timeout, ss);
	ss->flags = 0;
}
