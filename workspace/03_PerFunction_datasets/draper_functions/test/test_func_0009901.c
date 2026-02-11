append_dict_valist(DBusMessageIter *iter,
					const char *first_key,
					va_list var_args)
{
	DBusMessageIter dict;
	const char *key;
	int type;
	int n_elements;
	void *val;

	dbus_message_iter_open_container(iter, DBUS_TYPE_ARRAY,
			DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
			DBUS_TYPE_STRING_AS_STRING DBUS_TYPE_VARIANT_AS_STRING
			DBUS_DICT_ENTRY_END_CHAR_AS_STRING, &dict);

	key = first_key;
	while (key) {
		type = va_arg(var_args, int);
		val = va_arg(var_args, void *);
		if (type == DBUS_TYPE_ARRAY) {
			n_elements = va_arg(var_args, int);
			if (n_elements > 0)
				dict_append_array(&dict, key, DBUS_TYPE_STRING,
						val, n_elements);
		} else
			dict_append_entry(&dict, key, type, val);
		key = va_arg(var_args, char *);
	}

	dbus_message_iter_close_container(iter, &dict);
}
