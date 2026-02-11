interface_capability(const char *key, DBusMessageIter *iter,
							void *user_data)
{
	struct supplicant_interface *interface = user_data;

	if (key == NULL)
		return;

	if (g_strcmp0(key, "KeyMgmt") == 0)
		supplicant_dbus_array_foreach(iter,
				interface_capability_keymgmt, interface);
	else if (g_strcmp0(key, "AuthAlg") == 0)
		supplicant_dbus_array_foreach(iter,
				interface_capability_authalg, interface);
	else if (g_strcmp0(key, "Protocol") == 0)
		supplicant_dbus_array_foreach(iter,
				interface_capability_proto, interface);
	else if (g_strcmp0(key, "Pairwise") == 0)
		supplicant_dbus_array_foreach(iter,
				interface_capability_pairwise, interface);
	else if (g_strcmp0(key, "Group") == 0)
		supplicant_dbus_array_foreach(iter,
				interface_capability_group, interface);
	else if (g_strcmp0(key, "Scan") == 0)
		supplicant_dbus_array_foreach(iter,
				interface_capability_scan, interface);
	else if (g_strcmp0(key, "Modes") == 0)
		supplicant_dbus_array_foreach(iter,
				interface_capability_mode, interface);
	else
		DBG("key %s type %c",
				key, dbus_message_iter_get_arg_type(iter));
}
