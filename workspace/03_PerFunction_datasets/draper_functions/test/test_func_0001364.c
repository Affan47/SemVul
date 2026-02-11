e_goa_client_claim_one_orphan (EGoaClient *client,
                               GoaObject *new_goa_object)
{
	GHashTable *orphans;
	GoaAccount *goa_account;
	GoaObject *old_goa_object;
	const gchar *goa_account_id;

	orphans = client->priv->orphans;

	goa_account = goa_object_peek_account (new_goa_object);
	g_return_val_if_fail (goa_account != NULL, NULL);

	goa_account_id = goa_account_get_id (goa_account);
	g_return_val_if_fail (goa_account_id != NULL, NULL);

	g_mutex_lock (&client->priv->orphans_lock);

	old_goa_object = g_hash_table_lookup (orphans, goa_account_id);

	if (old_goa_object != NULL) {
		g_object_ref (old_goa_object);
		g_hash_table_remove (orphans, goa_account_id);
	}

	g_mutex_unlock (&client->priv->orphans_lock);

	if (old_goa_object != NULL)
		g_print (
			"GOA: Claiming orphaned account '%s'\n",
			goa_account_id);

	return old_goa_object;
}
