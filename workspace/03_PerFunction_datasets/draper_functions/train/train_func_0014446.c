interface_added(struct supplicant_interface *interface)
{
	const char *ifname = supplicant_interface_get_ifname(interface);
	const char *driver = supplicant_interface_get_driver(interface);

	DBG("* ifname %s driver %s", ifname, driver);

	if (supplicant_interface_scan(interface, scan_callback, NULL) < 0)
		DBG("scan failed");
}
