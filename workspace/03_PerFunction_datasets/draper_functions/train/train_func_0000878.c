serial_proxy_init(struct serial_adapter *adapter)
{
	GKeyFile *config;
	GError *gerr = NULL;
	const char *file = CONFIGDIR "/serial.conf";
	char **group_list;
	int i;

	config = g_key_file_new();

	if (!g_key_file_load_from_file(config, file, 0, &gerr)) {
		error("Parsing %s failed: %s", file, gerr->message);
		g_error_free(gerr);
		g_key_file_free(config);
		return;
	}

	group_list = g_key_file_get_groups(config, NULL);

	for (i = 0; group_list[i] != NULL; i++) {
		char *group_str = group_list[i], *uuid_str, *address;
		int err;
		struct serial_proxy *prx;


		if (strlen(group_str) < 5 || strncmp(group_str, "Proxy", 5))
			continue;

		uuid_str = g_key_file_get_string(config, group_str, "UUID",
									&gerr);
		if (gerr) {
			DBG("%s: %s", file, gerr->message);
			g_error_free(gerr);
			g_key_file_free(config);
			g_strfreev(group_list);
			return;
		}

		address = g_key_file_get_string(config, group_str, "Address",
									&gerr);
		if (gerr) {
			DBG("%s: %s", file, gerr->message);
			g_error_free(gerr);
			g_key_file_free(config);
			g_free(uuid_str);
			g_strfreev(group_list);
			return;
		}

		err = register_proxy(adapter, uuid_str, address, &prx);
		if (err == -EINVAL)
			error("Invalid address.");
		else if (err == -EALREADY)
			DBG("Proxy already exists.");
		else if (err < 0)
			error("Proxy creation failed (%s)", strerror(-err));
		else {
			err = enable_proxy(prx);
			if (err < 0)
				error("Proxy enable failed (%s)",
						strerror(-err));
		}

		g_free(uuid_str);
		g_free(address);
	}

	g_strfreev(group_list);
	g_key_file_free(config);
}
