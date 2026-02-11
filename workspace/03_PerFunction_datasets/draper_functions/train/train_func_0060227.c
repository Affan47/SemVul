e_credentials_has_key (const ECredentials *credentials,
                       const gchar *key)
{
	g_return_val_if_fail (credentials != NULL, FALSE);
	g_return_val_if_fail (credentials->priv != NULL, FALSE);
	g_return_val_if_fail (credentials->priv->keys != NULL, FALSE);
	g_return_val_if_fail (key != NULL, FALSE);
	g_return_val_if_fail (*key, FALSE);

	return g_hash_table_lookup (credentials->priv->keys, key) != NULL;
}
