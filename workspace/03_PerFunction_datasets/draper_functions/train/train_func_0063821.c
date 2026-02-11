lotus_rldb_data (LotusRLDB *rldb, gconstpointer p, size_t l)
{
	g_return_if_fail (rldb->pending_id == 0);
	while (rldb->ndims > 0) {
		g_return_if_fail (rldb->lower->len > 0);
		rldb = g_ptr_array_index (rldb->lower, rldb->lower->len - 1);
		g_return_if_fail (rldb != NULL);
	}

	g_return_if_fail (rldb->datanode == NULL);
	rldb->datanode = g_string_sized_new (l);
	g_string_append_len (rldb->datanode, p, l);
}
