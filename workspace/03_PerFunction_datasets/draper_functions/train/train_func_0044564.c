plugin_unregister(plugin_t *p)
{


	struct timer *t;
	session_t *s;
	query_t **ll;
	variable_t *v;
	command_t *c;
	list_t l;

	if (!p)
		return -1;


	for (l = watches; l; l = l->next) {
		watch_t *w = l->data;

		if (w && w->plugin == p)
			watch_free(w);
	}

	for (t = timers; t; t = t->next) {
		if (t->plugin == p)
			t = timers_removei(t);
	}

	for (s = sessions; s; ) {
		session_t *next = s->next;

		if (s->plugin == p)
			session_remove(s->uid);
		s = next;
	}

	for (ll = queries; ll <= &queries[QUERY_EXTERNAL]; ll++) {
		query_t *q;

		for (q = *ll; q; ) {
			query_t *next = q->next;

			if (q->plugin == p)
				query_free(q);

			q = next;
		}
	}

	for (v = variables; v; v = v->next) {
		if (v->plugin == p)
			v = variables_removei(v);
	}

	for (c = commands; c; c = c->next) {
		if (c->plugin == p)
			c = commands_removei(c);
	}

	plugins_unlink(p);

	return 0;
}
