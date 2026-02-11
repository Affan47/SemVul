copy_all_uids_to_hash (gpointer uid,
                       gpointer hash)
{
	g_return_if_fail (uid != NULL);

	g_hash_table_insert (hash, (gchar *) camel_pstring_strdup (uid), GINT_TO_POINTER (1));
}
