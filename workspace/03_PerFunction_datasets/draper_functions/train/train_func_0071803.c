io_capa_response(int index, void *ptr)
{
	struct dev_info *dev = &devs[index];
	evt_io_capability_response *evt = ptr;
	struct bt_conn *conn;
	char da[18];

	ba2str(&evt->bdaddr, da);
	DBG("hci%d IO capability response from %s", index, da);

	conn = find_connection(dev, &evt->bdaddr);
	if (conn) {
		conn->rem_cap = evt->capability;
		conn->rem_auth = evt->authentication;
		conn->rem_oob_data = evt->oob_data;
	}
}
