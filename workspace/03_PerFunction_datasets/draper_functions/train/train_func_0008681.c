link_key_notify(int index, void *ptr)
{
	struct dev_info *dev = &devs[index];
	evt_link_key_notify *evt = ptr;
	bdaddr_t *dba = &evt->bdaddr;
	struct link_key_info *key_info;
	uint8_t old_key_type, key_type;
	struct bt_conn *conn;
	GSList *match;
	char da[18];
	uint8_t status = 0;

	ba2str(dba, da);
	DBG("hci%d dba %s type %d", index, da, evt->key_type);

	conn = get_connection(dev, &evt->bdaddr);

	match = g_slist_find_custom(dev->keys, dba, (GCompareFunc) bacmp);
	if (match)
		key_info = match->data;
	else
		key_info = NULL;

	if (key_info == NULL) {
		key_info = g_new0(struct link_key_info, 1);
		bacpy(&key_info->bdaddr, &evt->bdaddr);
		old_key_type = 0xff;
	} else {
		dev->keys = g_slist_remove(dev->keys, key_info);
		old_key_type = key_info->type;
	}

	memcpy(key_info->key, evt->link_key, sizeof(evt->link_key));
	key_info->type = evt->key_type;
	key_info->pin_len = dev->pin_length;

	key_type = evt->key_type;

	DBG("key type 0x%02x old key type 0x%02x", key_type, old_key_type);
	DBG("local auth 0x%02x and remote auth 0x%02x",
					conn->loc_auth, conn->rem_auth);

	if (key_type == HCI_LK_CHANGED_COMBINATION) {


		if (conn->rem_auth == 0xff && old_key_type == 0xff)
			key_type = HCI_LK_COMBINATION;
		else if (old_key_type != 0xff)
			key_type = old_key_type;
		else


			goto done;
	}

	key_info->type = key_type;


	if (key_type == HCI_LK_DEBUG_COMBINATION)
		goto done;


	if (key_type < HCI_LK_DEBUG_COMBINATION ||
			(key_type == HCI_LK_CHANGED_COMBINATION
					&& old_key_type != HCI_LK_INVALID) ||
			(conn->loc_auth > 0x01 && conn->rem_auth > 0x01) ||
			(conn->loc_auth == 0x02 || conn->loc_auth == 0x03) ||
			(conn->rem_auth == 0x02 || conn->rem_auth == 0x03)) {
		int err;

		err = btd_event_link_key_notify(&dev->bdaddr, dba,
						evt->link_key, key_type,
						dev->pin_length);

		if (err == -ENODEV)
			status = HCI_OE_LOW_RESOURCES;
		else if (err < 0)
			status = HCI_MEMORY_FULL;

		goto done;
	}

done:
	dev->pin_length = 0;

	if (status != 0) {
		g_free(key_info);
		bonding_complete(dev, conn, status);
		disconnect_addr(index, dba, status);
		return;
	}

	dev->keys = g_slist_prepend(dev->keys, key_info);


	if (!conn->bonding_initiator && conn->handle != 0)
		bonding_complete(dev, conn, 0);
}
