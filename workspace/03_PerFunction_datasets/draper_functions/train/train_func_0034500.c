plugin_unload(plugin_t *p) {
	struct timer *t;
	query_t **ll;
	variable_t *v;
	command_t *c;
	list_t l;

	p->destroy();

	if (p == ui_plugin)
		ui_plugin = NULL;
	else
		debug_error("plugin_unload() but no ui_plugin!\n");


	for (l = watches; l; l = l->next) {
		watch_t *w = l->data;

		if (w && w->plugin == p)
			watch_free(w);
	}

	for (t = timers; t; t = t->next) {
		if (t->plugin == p)
			t = timers_removei(t);
	}

	for (ll = queries; ll <= &queries[QUERY_EXTERNAL]; ll++) {
		query_t *q;

		for (q = *ll; q; ) {
			query_t *next = q->next;

			if (q->plugin == p)
				LIST_REMOVE2(&queries[q->id >= QUERY_EXTERNAL ? QUERY_EXTERNAL : q->id], q, NULL);

			q = next;
		}
	}

	for (v = variables; v; v = v->next) {
		if (v->plugin == p)
			v = variables_removei(v);
	}

	for (c = commands; c; c = c->next) {
		if (c->__plugin == p)
			c = commands_removei(c);
	}

	if (p->__dl)
		ekg2_dlclose(p->__dl);
}
