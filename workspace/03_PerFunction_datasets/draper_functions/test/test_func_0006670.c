get_auto_method(const char *peername, const char *filename)
{
	const struct csync_group *g = 0;
	const struct csync_group_host *h;

	while ( (g=csync_find_next(g, filename)) ) {
		for (h = g->host; h; h = h->next) {
			if (!strcmp(h->hostname, peername)) {
				if (g->auto_method == CSYNC_AUTO_METHOD_LEFT && h->on_left_side)
					return CSYNC_AUTO_METHOD_LEFT_RIGHT_LOST;
				if (g->auto_method == CSYNC_AUTO_METHOD_RIGHT && !h->on_left_side)
					return CSYNC_AUTO_METHOD_LEFT_RIGHT_LOST;
				return g->auto_method;
			}
		}
	}

	return CSYNC_AUTO_METHOD_NONE;
}
