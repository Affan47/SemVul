query_id(const char *name) {
	struct query_def *a = NULL;
	list_t l;
	int i;

	for (i=0; i < QUERY_EXTERNAL; i++) {
		if (!xstrcmp(query_list[i].name, name)) {
#ifdef DDEBUG
			debug_error("Use query_connect_id()/query_emit_id() for: %s\n", name);
#endif
			return query_list[i].id;
		}
	}

	for (l = queries_external; l; l = l->next) {
		a = l->data;

		if (!xstrcmp(a->name, name))
			return a->id;
	}
	debug_error("query_id() NOT FOUND[%d]: %s\n", queries_count - QUERY_EXTERNAL, __(name));

	a	= xmalloc(sizeof(struct query_def));
	a->id	= queries_count++;
	a->name	= xstrdup(name);

	list_add(&queries_external, a);

	return a->id;
}
