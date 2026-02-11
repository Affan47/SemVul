mgmt_passkey_notify(int sk, uint16_t index, void *buf, size_t len)
{
	struct mgmt_ev_passkey_notify *ev = buf;
	struct controller_info *info;
	uint32_t passkey;
	char addr[18];
	int err;

	if (len < sizeof(*ev)) {
		error("Too small passkey_notify event");
		return;
	}

	ba2str(&ev->addr.bdaddr, addr);

	DBG("hci%u %s", index, addr);

	if (index > max_index) {
		error("Unexpected index %u in passkey_notify event", index);
		return;
	}

	info = &controllers[index];

	passkey = bt_get_le32(&ev->passkey);

	DBG("passkey %06u entered %u", passkey, ev->entered);

	err = btd_event_user_notify(&info->bdaddr, &ev->addr.bdaddr,
				    passkey, ev->entered);
	if (err < 0)
		error("btd_event_user_notify: %s", strerror(-err));
}
