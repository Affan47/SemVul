notify_announce_online (server * serv, struct notify_per_server *servnot,
								char *nick, const message_tags_data *tags_data)
{
	session *sess;

	sess = serv->front_session;

	servnot->lastseen = time (0);
	if (servnot->ison)
		return;

	servnot->ison = TRUE;
	servnot->laston = time (0);
	EMIT_SIGNAL_TIMESTAMP (XP_TE_NOTIFYONLINE, sess, nick, serv->servername,
					 server_get_network (serv, TRUE), NULL, 0,
					 tags_data->timestamp);
	fe_notify_update (nick);
	fe_notify_update (0);

	if (prefs.hex_notify_whois_online)
	{


	    char *wii_str = malloc (strlen (nick) * 2 + 2);
	    sprintf (wii_str, "%s %s", nick, nick);
	    serv->p_whois (serv, wii_str);
	    free (wii_str);
	}
}
