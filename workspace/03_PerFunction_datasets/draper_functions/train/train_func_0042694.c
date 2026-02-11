e_xmlhash_compare (EXmlHash *hash,
                   const gchar *key,
                   const gchar *compare_data)
{
	gchar *data;
	gint rc;

	g_return_val_if_fail (hash != NULL, E_XMLHASH_STATUS_NOT_FOUND);
	g_return_val_if_fail (key != NULL, E_XMLHASH_STATUS_NOT_FOUND);
	g_return_val_if_fail (compare_data != NULL, E_XMLHASH_STATUS_NOT_FOUND);

	data = g_hash_table_lookup (hash->objects, key);
	if (!data)
		return E_XMLHASH_STATUS_NOT_FOUND;

	rc = strcmp (data, compare_data);
	if (rc == 0)
		return E_XMLHASH_STATUS_SAME;

	return E_XMLHASH_STATUS_DIFFERENT;
}
