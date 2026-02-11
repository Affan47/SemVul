event_away(IRC_SERVER_REC *server, const char *data)
{
	char *params, *nick, *awaymsg, *recoded;

	g_return_if_fail(data != NULL);

	params = event_get_params(data, 3, NULL, &nick, &awaymsg);
	recoded = recode_in(SERVER(server), awaymsg, nick);
	if (!settings_get_bool("show_away_once") ||
	    last_away_nick == NULL || g_strcasecmp(last_away_nick, nick) != 0 ||
	    last_away_msg == NULL || g_strcasecmp(last_away_msg, awaymsg) != 0) {


		g_free_not_null(last_away_nick);
		g_free_not_null(last_away_msg);
		last_away_nick = g_strdup(nick);
		last_away_msg = g_strdup(awaymsg);

		printformat(server, nick, MSGLEVEL_CRAP,
			    IRCTXT_NICK_AWAY, nick, recoded);
	}
	g_free(params);
	g_free(recoded);
}
