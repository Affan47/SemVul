enslave_slave (NMDevice *device, NMDevice *slave, NMConnection *connection)
{
	gboolean success, no_firmware = FALSE;
	const char *iface = nm_device_get_ip_iface (device);
	const char *slave_iface = nm_device_get_ip_iface (slave);

	nm_device_hw_take_down (slave, TRUE);

	success = nm_system_bond_enslave (nm_device_get_ip_ifindex (device),
	                                  iface,
	                                  nm_device_get_ip_ifindex (slave),
	                                  slave_iface);

	nm_device_hw_bring_up (slave, TRUE, &no_firmware);

	if (success) {
		nm_log_info (LOGD_BOND, "(%s): enslaved bond slave %s", iface, slave_iface);
		g_object_notify (G_OBJECT (device), "slaves");
	}

	return success;
}
