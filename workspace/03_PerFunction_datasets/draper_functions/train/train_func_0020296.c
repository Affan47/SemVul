delegate_hash_table_remove (MonoDelegate *d)
{
	guint32 gchandle = 0;

	mono_marshal_lock ();
	if (delegate_hash_table == NULL)
		delegate_hash_table = delegate_hash_table_new ();
	if (mono_gc_is_moving ())
		gchandle = GPOINTER_TO_UINT (g_hash_table_lookup (delegate_hash_table, d->delegate_trampoline));
	g_hash_table_remove (delegate_hash_table, d->delegate_trampoline);
	mono_marshal_unlock ();
	if (mono_gc_is_moving ())
		mono_gchandle_free (gchandle);
}
