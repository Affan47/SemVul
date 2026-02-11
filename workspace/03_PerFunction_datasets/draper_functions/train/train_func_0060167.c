pk_store_set_strv (PkStore *store, const gchar *key, gchar **data)
{
	gboolean ret;

	g_return_val_if_fail (PK_IS_STORE (store), FALSE);
	g_return_val_if_fail (key != NULL, FALSE);


	if (data == NULL)
		return FALSE;


	ret = g_hash_table_remove (store->priv->hash_strv, key);
	if (ret)
		g_debug ("already set data for %s, so removing", key);

	g_debug ("saving %p for %s", data, key);
	g_hash_table_insert (store->priv->hash_strv, g_strdup (key), (gpointer) g_strdupv (data));
	return TRUE;
}
