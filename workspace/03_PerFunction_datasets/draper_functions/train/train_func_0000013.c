camel_pointer_tracker_untrack (gpointer ptr)
{
	g_return_if_fail (ptr != NULL);

	G_LOCK (ptr_tracker);

	if (!ptr_tracker)
		g_printerr ("Pointer tracker not initialized, thus cannot remove %p\n", ptr);
	else if (!g_hash_table_lookup (ptr_tracker, ptr))
		g_printerr ("Pointer %p is not tracked\n", ptr);
	else
		g_hash_table_remove (ptr_tracker, ptr);

	G_UNLOCK (ptr_tracker);
}
