e_goa_client_claim_all_orphans (EGoaClient *client)
{
	GList *list;

	g_mutex_lock (&client->priv->orphans_lock);

	list = g_hash_table_get_values (client->priv->orphans);
	g_list_foreach (list, (GFunc) g_object_ref, NULL);
	g_hash_table_remove_all (client->priv->orphans);

	g_mutex_unlock (&client->priv->orphans_lock);

	if (list != NULL)
		g_print ("GOA: Claiming orphaned account(s)\n");

	return list;
}
