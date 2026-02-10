hdp_establish_mcl(struct hdp_device *device,
						hdp_continue_proc_f func,
						gpointer data,
						GDestroyNotify destroy,
						GError **err)
{
	struct conn_mcl_data *conn_data;
	bdaddr_t dst, src;
	uuid_t uuid;

	device_get_address(device->dev, &dst, NULL);
	adapter_get_address(device_get_adapter(device->dev), &src);

	conn_data = g_new0(struct conn_mcl_data, 1);
	conn_data->refs = 1;
	conn_data->func = func;
	conn_data->data = data;
	conn_data->destroy = destroy;
	conn_data->dev = health_device_ref(device);

	bt_string2uuid(&uuid, HDP_UUID);
	if (bt_search_service(&src, &dst, &uuid, search_cb, conn_data,
						destroy_con_mcl_data) < 0) {
		g_set_error(err, HDP_ERROR, HDP_CONNECTION_ERROR,
						"Can't get remote SDP record");
		g_free(conn_data);
		return FALSE;
	}

	return TRUE;
}
