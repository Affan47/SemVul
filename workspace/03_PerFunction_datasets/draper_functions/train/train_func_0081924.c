remove_cm_context(struct modem_data *modem,
				const char *context_path)
{
	if (modem->context == NULL)
		return;

	if (modem->network != NULL)
		remove_network(modem);

	g_hash_table_remove(context_hash, context_path);

	network_context_free(modem->context);
	modem->context = NULL;

	modem->valid_apn = FALSE;

	if (modem->network != NULL)
		remove_network(modem);
}
