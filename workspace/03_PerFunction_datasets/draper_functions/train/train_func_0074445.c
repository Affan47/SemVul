update_order(void)
{
	GHashTableIter iter;
	gpointer value, key;

	DBG("");

	g_hash_table_iter_init(&iter, gateway_hash);

	while (g_hash_table_iter_next(&iter, &key, &value) == TRUE) {
		struct gateway_data *data = value;

		data->order = __connman_service_get_order(data->service);
	}
}
