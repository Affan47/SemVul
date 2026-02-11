reply_pending_requests(struct btd_adapter *adapter)
{
	GSList *l;

	if (!adapter)
		return;


	for (l = adapter->devices; l; l = l->next) {
		struct btd_device *device = l->data;

		if (device_is_bonding(device, NULL))
			device_cancel_bonding(device,
						HCI_OE_USER_ENDED_CONNECTION);
	}
}
