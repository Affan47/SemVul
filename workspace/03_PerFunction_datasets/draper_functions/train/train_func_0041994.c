btd_event_user_notify(bdaddr_t *sba, bdaddr_t *dba, uint32_t passkey)
{
	struct btd_adapter *adapter;
	struct btd_device *device;

	if (!get_adapter_and_device(sba, dba, &adapter, &device, TRUE))
		return -ENODEV;

	return device_request_authentication(device, AUTH_TYPE_NOTIFY_PASSKEY,
							&passkey, FALSE, NULL);
}
