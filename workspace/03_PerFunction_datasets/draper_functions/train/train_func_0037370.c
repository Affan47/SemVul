dma_sparse_buffer_add_mark (DmaSparseBuffer *buffer, guint address, gint mark)
{
	gint markers;

	if (buffer->mark == NULL)
	{

		buffer->mark = g_hash_table_new (g_direct_hash, g_direct_equal);
	}


	markers = GPOINTER_TO_INT (g_hash_table_lookup (buffer->mark, GINT_TO_POINTER (address)));
	markers |= 1 << mark;
	g_hash_table_replace (buffer->mark, GINT_TO_POINTER (address), GINT_TO_POINTER (markers));
}
