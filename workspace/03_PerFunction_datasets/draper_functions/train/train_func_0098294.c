get_bus_name (GUdevClient *uclient, NMDevice *device)
{
	GUdevDevice *udevice;
	const char *ifname, *bus;
	char *display_bus;

	bus = g_object_get_data (G_OBJECT (device), BUS_TAG);
	if (bus) {
		if (*bus)
			return bus;
		else
			return NULL;
	}

	ifname = nm_device_get_iface (device);
	if (!ifname)
		return NULL;

	udevice = g_udev_client_query_by_subsystem_and_name (uclient, "net", ifname);
	if (!udevice)
		udevice = g_udev_client_query_by_subsystem_and_name (uclient, "tty", ifname);
	if (!udevice)
		return NULL;

	bus = g_udev_device_get_property (udevice, "ID_BUS");
	if (!g_strcmp0 (bus, "pci"))
		display_bus = g_strdup (_("PCI"));
	else if (!g_strcmp0 (bus, "usb"))
		display_bus = g_strdup (_("USB"));
	else {


		display_bus = g_strdup ("");
	}

	g_object_set_data_full (G_OBJECT (device),
	                        BUS_TAG, display_bus,
	                        (GDestroyNotify) g_free);
	if (*display_bus)
		return display_bus;
	else
		return NULL;
}
