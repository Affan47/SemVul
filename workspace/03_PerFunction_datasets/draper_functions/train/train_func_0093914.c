parse_dict(struct dict_entry_func dict_context[],
							DBusMessageIter *iter,
							GError **err,
							gpointer user_data)
{
	int ctype;
	DBusMessageIter dict;

	ctype = dbus_message_iter_get_arg_type(iter);
	if (ctype != DBUS_TYPE_ARRAY) {
		g_set_error(err, HDP_ERROR, HDP_DIC_PARSE_ERROR,
					"Dictionary should be an array");
		return FALSE;
	}

	dbus_message_iter_recurse(iter, &dict);
	while ((ctype = dbus_message_iter_get_arg_type(&dict)) !=
							DBUS_TYPE_INVALID) {
		if (ctype != DBUS_TYPE_DICT_ENTRY) {
			g_set_error(err, HDP_ERROR, HDP_DIC_PARSE_ERROR,
						"Dictionary array should "
						"contain dict entries");
			return FALSE;
		}


		if (!parse_dict_entry(dict_context, &dict, err,
							user_data))
			return FALSE;


		dbus_message_iter_next(&dict);
	}

	return TRUE;
}
