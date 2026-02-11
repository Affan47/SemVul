window_find_sa(session_t *session, const char *target, int session_null_means_no_session) {
	userlist_t *u;
	window_t *w;

	if (!target || !xstrcasecmp(target, "__current"))
		return window_current->id ? window_current : window_status;

	if ((!xstrcasecmp(target, "__status")))
		return window_status;

	if (!xstrcasecmp(target, "__debug"))
		return window_debug;

	for (w = windows; w; w = w->next) {

		if (w->target && ((session == w->session) || (!session && !session_null_means_no_session)) && !xstrcasecmp(target, w->target))
			return w;
	}


	if (!session && session_null_means_no_session)
		return NULL;

	if (strncmp(target, "__", 2)) {
		session_t *s;
		for (s = sessions; s; s = s->next) {

			if (session != s && session)
				continue;


			if (!(u = userlist_find(s, target)))
				continue;

			for (w = windows; w; w = w->next) {

				if ((!session || session == w->session) && w->target) {
					if (u->nickname && !xstrcasecmp(u->nickname, w->target))
						return w;


					if (!xstrcasecmp(u->uid, w->target))
						return w;
				}
			}
		}
	}
	return NULL;
}
