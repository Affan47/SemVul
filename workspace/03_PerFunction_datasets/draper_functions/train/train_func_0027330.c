irc_autorejoin(session_t *s, int when, char *chan) {
	irc_private_t *j;
	string_t st;
	window_t *w;
	char *chanprefix;
	int rejoin;

#if 1
	if (!s || !(j = s->priv) || (s->plugin != &irc_plugin))
		return -1;
#endif
	chanprefix = SOP(_005_CHANTYPES);
	rejoin = session_int_get(s, "REJOIN");

	if (!(rejoin&(1<<(when))))
		return -1;

	switch (when) {
		case IRC_REJOIN_CONNECT:
			st = string_init(NULL);
			for (w = windows; w; w = w->next) {
				if (!w->target || w->session != s)
					continue;

				if (valid_plugin_uid(s->plugin, w->target) != 1)
					continue;

				if (!xstrchr(chanprefix, (w->target)[4]))
					continue;

				if (st->len)
					string_append_c(st, ',');
				if ((w->target)[4] == '!') {
					string_append_c(st, '!');
					string_append(st, w->target + 10);
				} else {
					string_append(st, w->target + 4);
				}
			}
			if (st->len)
				watch_write(j->send_watch, "JOIN %s\r\n", st->str);
			string_free(st, 1);
			break;

		case IRC_REJOIN_KICK:
			watch_write(j->send_watch, "JOIN %s\r\n", chan);
			break;

		default:
			return -1;
	}
	return 0;
}
