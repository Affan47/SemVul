__connman_wpad_stop(struct connman_service *service)
{
	int index;

	DBG("service %p", service);

	if (wpad_list == NULL)
		return;

	index = __connman_service_get_index(service);
	if (index < 0)
		return;

	if (g_hash_table_remove(wpad_list, GINT_TO_POINTER(index)) == TRUE)
		connman_service_unref(service);
}
