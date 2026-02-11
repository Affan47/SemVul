ekg2_bless_irc_server(HV *hv, session_t *session)
{
	irc_private_t *j = irc_private(session);
	connector_t   *s = NULL;
	if (xstrncasecmp( session_uid_get( (session_t *) session), IRC4, 4)) {
		debug("[perl_ierror] not irc session in ekg2_bless_irc_server!\n");
		return;
	}
	debug_bless("blessing server %s\n", session->uid);

	if (j->conntmplist && j->conntmplist->data) s = j->conntmplist->data;
	if (s) {
		(void) hv_store(hv, "server",  6, new_pv(s->hostname), 0);
		(void) hv_store(hv, "ip",      2, new_pv(s->address), 0);
	} else {
		(void) hv_store(hv, "server",  6, new_pv(session_get(session, "server")), 0);
		(void) hv_store(hv, "ip",      2, new_pv("0.0.0.0"), 0);
	}
	if (j->nick)	(void) hv_store(hv, "nick",    4, new_pv(j->nick), 0);
	else		(void) hv_store(hv, "nick",    4, new_pv(session_get(session, "nickname")), 0);
}
