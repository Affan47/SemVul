HeapDestroy (gpointer handle)
{
	HeapInfo *heap = (HeapInfo *) handle;


	if (handle == process_heap)
		return 0;

	g_hash_table_foreach (heap->hash, free_handles, NULL);
	g_hash_table_destroy (heap->hash);

	g_hash_table_remove (heaps, handle);
	g_free (heap);

	return 1;
}
