free_gateway_list (GSList *gateways)
{
	GSList *l;

	l = gateways;
	while (l) {
		Gateway *gw;

		gw = l->data;
		g_free (gw->mac);
		g_hash_table_destroy (gw->address);
		geoclue_accuracy_free (gw->accuracy);
		g_free (gw);

		l = l->next;
	}
	g_slist_free (gateways);
}
