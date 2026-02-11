nma_utils_disambiguate_device_names (NMDevice **devices,
                                     int        num_devices)
{
	static const char *subsys[3] = { "net", "tty", NULL };
	GUdevClient *uclient;
	char **names;
	gboolean *duplicates;
	int i;

	names = g_new (char *, num_devices + 1);
	duplicates = g_new (gboolean, num_devices);


	for (i = 0; i < num_devices; i++)
		names[i] = get_device_generic_type_name_with_iface (devices[i]);
	if (!find_duplicates (names, duplicates, num_devices))
		goto done;


	for (i = 0; i < num_devices; i++) {
		if (duplicates[i]) {
			g_free (names[i]);
			names[i] = get_device_type_name_with_iface (devices[i]);
		}
	}
	if (!find_duplicates (names, duplicates, num_devices))
		goto done;


	uclient = g_udev_client_new (subsys);
	for (i = 0; i < num_devices; i++) {
		if (duplicates[i]) {
			const char *bus = get_bus_name (uclient, devices[i]);
			char *name;

			if (!bus)
				continue;

			g_free (names[i]);
			name = get_device_type_name_with_iface (devices[i]);


			names[i] = g_strdup_printf (C_("long device name", "%s %s"),
			                            bus, name);
			g_free (name);
		}
	}
	g_object_unref (uclient);
	if (!find_duplicates (names, duplicates, num_devices))
		goto done;


	for (i = 0; i < num_devices; i++) {
		if (duplicates[i]) {
			const char *vendor = nma_utils_get_device_vendor (devices[i]);
			char *name;

			if (!vendor)
				continue;

			g_free (names[i]);
			name = get_device_type_name_with_iface (devices[i]);
			names[i] = g_strdup_printf (C_("long device name", "%s %s"),
			                            vendor,
			                            nma_utils_get_device_type_name (devices[i]));
			g_free (name);
		}
	}
	if (!find_duplicates (names, duplicates, num_devices))
		goto done;


	for (i = 0; i < num_devices; i++) {
		if (duplicates[i]) {
			const char *interface = nm_device_get_iface (devices[i]);

			if (!interface)
				continue;

			g_free (names[i]);
			names[i] = g_strdup_printf ("%s (%s)",
			                            nma_utils_get_device_type_name (devices[i]),
			                            interface);
		}
	}

 done:
	g_free (duplicates);
	names[num_devices] = NULL;
	return names;
}
