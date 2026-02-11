find_session(GSList *list, const bdaddr_t *dst)
{
	for (; list != NULL; list = g_slist_next(list)) {
		struct avctp *s = list->data;

		if (bacmp(dst, &s->dst))
			continue;

		return s;
	}

	return NULL;
}
