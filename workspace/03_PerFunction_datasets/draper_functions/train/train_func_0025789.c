hdp_adapter_register(DBusConnection *conn, struct btd_adapter *adapter)
{
	struct hdp_adapter *hdp_adapter;

	hdp_adapter = g_new0(struct hdp_adapter, 1);
	hdp_adapter->btd_adapter = btd_adapter_ref(adapter);

	if(!update_adapter(hdp_adapter))
		goto fail;

	adapters = g_slist_append(adapters, hdp_adapter);

	return 0;

fail:
	btd_adapter_unref(hdp_adapter->btd_adapter);
	g_free(hdp_adapter);
	return -1;
}
