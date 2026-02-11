message_forget(const struct guid *muid, uint8 function, gnutella_node_t *node)
{
	bool found;
	struct message *m;
	GSList *sl;
	GSList *t;
	struct route_data *route;

	g_assert(muid != NULL);
	node_check(node);

	found = find_message(muid, function, &m);
	g_return_unless(found);
	g_assert(m != NULL);

	route = get_routing_data(node);
	g_return_unless(route != NULL);

	for (
		sl = m->routes, t = m->ttls;
		sl != NULL;
		sl = g_slist_next(sl), t = g_slist_next(t)
	) {
		struct route_data *rd = sl->data;

		if (route == rd) {
			m->routes = g_slist_remove_link(m->routes, sl);
			if (t != NULL)
				m->ttls = g_slist_remove_link(m->ttls, t);
			remove_one_message_reference(rd);
			break;
		}
	}
}
