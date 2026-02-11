__connmanctl_dbus_print(DBusMessageIter *iter, const char *pre,
		const char *dict, const char *sep)
{
	int arg_type;
	dbus_bool_t b;
	unsigned char c;
	unsigned int i;
	double d;

	char *str;
	DBusMessageIter entry;

	if (pre == NULL)
		pre = "";

	while ((arg_type = dbus_message_iter_get_arg_type(iter))
			!= DBUS_TYPE_INVALID) {

		fprintf(stdout, "%s", pre);

		switch (arg_type) {
		case DBUS_TYPE_STRUCT:
			fprintf(stdout, "{ ");
			dbus_message_iter_recurse(iter, &entry);
			__connmanctl_dbus_print(&entry, "", "=", " ");
			fprintf(stdout, " }");
			break;

		case DBUS_TYPE_ARRAY:
			fprintf(stdout, "[ ");

			dbus_message_iter_recurse(iter, &entry);
			__connmanctl_dbus_print(&entry, "", "=", ", ");

			fprintf(stdout, " ]");
			break;

		case DBUS_TYPE_DICT_ENTRY:

			dbus_message_iter_recurse(iter, &entry);
			__connmanctl_dbus_print(&entry, "", dict, dict);
			break;

		case DBUS_TYPE_STRING:
		case DBUS_TYPE_OBJECT_PATH:
			dbus_message_iter_get_basic(iter, &str);
			fprintf(stdout, "%s", str);
			break;

		case DBUS_TYPE_VARIANT:
			dbus_message_iter_recurse(iter, &entry);
			__connmanctl_dbus_print(&entry, pre, dict, sep);
			break;

		case DBUS_TYPE_BOOLEAN:
			dbus_message_iter_get_basic(iter, &b);
			if (b == FALSE)
				fprintf(stdout, "False");
			else
				fprintf(stdout, "True");
			break;

		case DBUS_TYPE_BYTE:
			dbus_message_iter_get_basic(iter, &c);
			fprintf(stdout, "%d", c);
			break;

		case DBUS_TYPE_UINT16:
		case DBUS_TYPE_UINT32:
			dbus_message_iter_get_basic(iter, &i);
			fprintf(stdout, "%d", i);
			break;

		case DBUS_TYPE_DOUBLE:
			dbus_message_iter_get_basic(iter, &d);
			fprintf(stdout, "%f", d);
			break;

		default:
			fprintf(stdout, "<type %c>", arg_type);
			break;
		}

		if (dbus_message_iter_has_next(iter) == TRUE)
			fprintf(stdout, "%s", sep);

		dbus_message_iter_next(iter);
	}
}
