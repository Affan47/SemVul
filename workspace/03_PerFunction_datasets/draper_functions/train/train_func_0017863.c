interface_capability_mode(DBusMessageIter *iter, void *user_data)
{
	struct supplicant_interface *interface = user_data;
	const char *str = NULL;
	int i;

	dbus_message_iter_get_basic(iter, &str);
	if (str == NULL)
		return;

	for (i = 0; mode_capa_map[i].str != NULL; i++)
		if (strcmp(str, mode_capa_map[i].str) == 0) {
			interface->mode_capa |= mode_capa_map[i].val;
			break;
		}
}
