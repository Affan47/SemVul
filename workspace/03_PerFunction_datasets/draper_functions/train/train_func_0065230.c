remote_version_information(int index, void *ptr)
{
	struct dev_info *dev = &devs[index];
	evt_read_remote_version_complete *evt = ptr;
	struct bt_conn *conn;

	DBG("hci%d status %u", index, evt->status);

	if (evt->status)
		return;

	conn = find_conn_by_handle(dev, btohs(evt->handle));
	if (conn == NULL)
		return;

	write_version_info(&dev->bdaddr, &conn->bdaddr,
				btohs(evt->manufacturer), evt->lmp_ver,
				btohs(evt->lmp_subver));
}
