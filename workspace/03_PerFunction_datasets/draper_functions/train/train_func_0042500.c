sig_query_destroyed(QUERY_REC *query_destroyed)
{
	XMPP_QUERY_REC *query;

	query = XMPP_QUERY(query_destroyed);
	if (query != NULL && query->composing_time != 0
	    && IS_ALIVE_SERVER(query->server))
		signal_emit("xmpp composing stop", 2, query->server,
		    query->name);
}
