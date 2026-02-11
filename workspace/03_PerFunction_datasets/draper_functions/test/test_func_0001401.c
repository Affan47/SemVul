module_unload(module_t * m)
{
	mowgli_node_t *n, *tn;

	if (!m)
		return;


	while (m->dephost.head != NULL)
		module_unload((module_t *) m->dephost.head->data);


	MOWGLI_ITER_FOREACH_SAFE(n, tn, m->deplist.head)
	{
		module_t *hm = (module_t *) n->data;
		mowgli_node_t *hn = mowgli_node_find(m, &hm->dephost);

		mowgli_node_delete(hn, &hm->dephost);
		mowgli_node_free(hn);
		mowgli_node_delete(n, &m->deplist);
		mowgli_node_free(n);
	}

	n = mowgli_node_find(m, &modules);
	if (n != NULL)
	{
		slog(LG_INFO, "module_unload(): unloaded \2%s\2", m->header->name);
		if (me.connected)
		{
			wallops(_("Module %s unloaded."), m->header->name);
		}

		if (m->header->deinit)
			m->header->deinit();
		mowgli_node_delete(n, &modules);
		mowgli_node_free(n);
	}

	linker_close(m->handle);
	mowgli_heap_free(module_heap, m);
}
