mono_method_alloc_generic_virtual_thunk (MonoDomain *domain, int size)
{
	static gboolean inited = FALSE;
	static int generic_virtual_thunks_size = 0;

	guint32 *p;
	int i;
	MonoThunkFreeList **l;

	init_thunk_free_lists (domain);

	size += sizeof (guint32);
	if (size < sizeof (MonoThunkFreeList))
		size = sizeof (MonoThunkFreeList);

	i = list_index_for_size (size);
	for (l = &domain->thunk_free_lists [i]; *l; l = &(*l)->next) {
		if ((*l)->size >= size) {
			MonoThunkFreeList *item = *l;
			*l = item->next;
			return ((guint32*)item) + 1;
		}
	}


	while (++i < NUM_FREE_LISTS) {
		MonoThunkFreeList *item = domain->thunk_free_lists [i];
		if (!item)
			continue;
		g_assert (item->size > size);
		domain->thunk_free_lists [i] = item->next;
		return ((guint32*)item) + 1;
	}


	if (!inited) {
		mono_counters_register ("Generic virtual thunk bytes",
				MONO_COUNTER_GENERICS | MONO_COUNTER_INT, &generic_virtual_thunks_size);
		inited = TRUE;
	}
	generic_virtual_thunks_size += size;

	p = mono_domain_code_reserve (domain, size);
	*p = size;

	mono_domain_lock (domain);
	if (!domain->generic_virtual_thunks)
		domain->generic_virtual_thunks = g_hash_table_new (NULL, NULL);
	g_hash_table_insert (domain->generic_virtual_thunks, p, p);
	mono_domain_unlock (domain);

	return p + 1;
}
