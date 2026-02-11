btd_event_set_legacy_pairing(bdaddr_t *local, bdaddr_t *peer,
							gboolean legacy)
{
	struct btd_adapter *adapter;
	struct remote_dev_info *dev;

	adapter = manager_find_adapter(local);
	if (!adapter) {
		error("No matching adapter found");
		return;
	}

	dev = adapter_search_found_devices(adapter, peer);
	if (dev)
		dev->legacy = legacy;
}
