sig_not_in_roster(XMPP_SERVER_REC *server, const char *jid)
{
	g_return_if_fail(IS_SERVER(server));
	g_return_if_fail(jid != NULL);
	printformat_module(MODULE_NAME, server, NULL,
	    MSGLEVEL_CLIENTERROR, XMPPTXT_NOT_IN_ROSTER, jid);
}
