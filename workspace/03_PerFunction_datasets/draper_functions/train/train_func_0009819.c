sdp_record_remove(uint32_t handle)
{
	sdp_list_t *p = record_locate(handle);
	sdp_record_t *r;
	sdp_access_t *a;

	if (!p) {
		error("Remove : Couldn't find record for : 0x%x", handle);
		return -1;
	}

	r = p->data;
	if (r)
		service_db = sdp_list_remove(service_db, r);

	p = access_locate(handle);
	if (p == NULL || p->data == NULL)
		return 0;

	a = p->data;

	if (bacmp(&a->device, BDADDR_ANY) != 0) {
		struct btd_adapter *adapter = manager_find_adapter(&a->device);
		if (adapter)
			adapter_service_remove(adapter, r);
	} else
		manager_foreach_adapter(adapter_service_remove, r);

	access_db = sdp_list_remove(access_db, a);
	access_free(a);

	return 0;
}
