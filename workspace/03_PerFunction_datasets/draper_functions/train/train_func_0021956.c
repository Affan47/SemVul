myuser_access_find(myuser_t *mu, const char *mask)
{
	mowgli_node_t *n;

	if (mu == NULL || mask == NULL)
	{
		slog(LG_DEBUG, "myuser_access_find(): invalid parameters: mu = %p, mask = %p", mu, mask);
		return NULL;
	}

	MOWGLI_ITER_FOREACH(n, mu->access_list.head)
	{
		char *entry = (char *) n->data;

		if (!strcasecmp(entry, mask))
			return entry;
	}
	return NULL;
}
