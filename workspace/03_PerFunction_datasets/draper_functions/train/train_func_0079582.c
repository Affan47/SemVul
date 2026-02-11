parse_network_properties(DBusMessageIter *properties)
{
	int i;


	for (i = 0; ofono_indicators[i].desc != NULL; i++) {
		if (g_str_equal(ofono_indicators[i].desc, "battchg"))
			ofono_indicators[i].val = 5;
		else
			ofono_indicators[i].val = 0;
	}

	while (dbus_message_iter_get_arg_type(properties)
						== DBUS_TYPE_DICT_ENTRY) {
		const char *key;
		DBusMessageIter value, entry;

		dbus_message_iter_recurse(properties, &entry);
		dbus_message_iter_get_basic(&entry, &key);

		dbus_message_iter_next(&entry);
		dbus_message_iter_recurse(&entry, &value);

		handle_network_property(key, &value);

		dbus_message_iter_next(properties);
	}

	return 0;
}
