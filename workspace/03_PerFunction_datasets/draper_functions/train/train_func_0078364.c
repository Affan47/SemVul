mono_marshal_free_ccw_entry (gpointer key, gpointer value, gpointer user_data)
{
	g_hash_table_remove (ccw_interface_hash, value);
	g_assert (value);
	g_free (value);
	return TRUE;
}
