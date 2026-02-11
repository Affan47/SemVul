mono_lls_remove (MonoLinkedListSet *list, MonoThreadHazardPointers *hp, MonoLinkedListSetNode *value)
{
	MonoLinkedListSetNode *cur, **prev, *next;
	while (1) {
		if (!mono_lls_find (list, hp, value->key))
			return FALSE;

		next = mono_hazard_pointer_get_val (hp, 0);
		cur = mono_hazard_pointer_get_val (hp, 1);
		prev = mono_hazard_pointer_get_val (hp, 2);

		g_assert (cur == value);

		if (InterlockedCompareExchangePointer ((volatile gpointer*)&cur->next, mask (next, 1), next) != next)
			continue;

		mono_memory_write_barrier ();
		if (InterlockedCompareExchangePointer ((volatile gpointer*)prev, next, cur) == cur) {

			mono_memory_write_barrier ();
			mono_hazard_pointer_clear (hp, 1);
			if (list->free_node_func)
				mono_thread_hazardous_free_or_queue (value, list->free_node_func, FALSE, TRUE);
		} else
			mono_lls_find (list, hp, value->key);
		return TRUE;
	}
}
