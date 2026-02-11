session_remove(const char *uid)
{
	session_t *s;
	window_t *w;
	char *tmp;
	int count;
	list_t l;

	if (!(s = session_find(uid)))
		return -1;
	if (s == session_current)
		session_current = NULL;

	count = sessions_count();

	for (w = windows; w; w = w->next) {
		if (w->session == s) {
			w->session = NULL;
			if (count > 1)
				window_session_cycle(w);
		}
	}

	if (s->connected)
		command_exec_format(NULL, s, 1, ("/disconnect %s"), s->uid);
#ifdef HAVE_FLOCK
	if (s->lock_fd != -1) {
		flock(s->lock_fd, LOCK_UN);
		close(s->lock_fd);

	}
#endif


	for (l = watches; l; l = l->next) {
		watch_t *w = l->data;

		if (w && w->is_session && w->data == s)
			watch_free(w);

	}

	{
		struct timer *t;

		for (t = timers; t; t = t->next) {
			if (t->is_session && t->data == s)
				t = timers_removei(t);
		}
	}

	tmp = xstrdup(uid);
	query_emit_id(NULL, SESSION_CHANGED);
	query_emit_id(NULL, SESSION_REMOVED, &tmp);
	xfree(tmp);

	sessions_remove(s);
	return 0;
}
