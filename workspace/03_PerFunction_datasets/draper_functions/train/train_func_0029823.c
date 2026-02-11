inbound_ping_reply (session *sess, char *timestring, char *from,
						  const message_tags_data *tags_data)
{
	unsigned long tim, nowtim, dif;
	int lag = 0;
	char outbuf[64];

	if (strncmp (timestring, "LAG", 3) == 0)
	{
		timestring += 3;
		lag = 1;
	}

	tim = strtoul (timestring, NULL, 10);
	nowtim = make_ping_time ();
	dif = nowtim - tim;

	sess->server->ping_recv = time (0);

	if (lag)
	{
		sess->server->lag_sent = 0;
		sess->server->lag = dif / 1000;
		fe_set_lag (sess->server, dif / 100000);
		return;
	}

	if (atol (timestring) == 0)
	{
		if (sess->server->lag_sent)
			sess->server->lag_sent = 0;
		else
			EMIT_SIGNAL_TIMESTAMP (XP_TE_PINGREP, sess, from, "?", NULL, NULL, 0,
										  tags_data->timestamp);
	} else
	{
		snprintf (outbuf, sizeof (outbuf), "%ld.%ld%ld", dif / 1000000, (dif / 100000) % 10, dif % 10);
		EMIT_SIGNAL_TIMESTAMP (XP_TE_PINGREP, sess, from, outbuf, NULL, NULL, 0,
									  tags_data->timestamp);
	}
}
