append_char_dict(DBusMessageIter *iter, struct characteristic *chr)
{
	DBusMessageIter dict;
	const char *name = "";
	char *uuid;

	dbus_message_iter_open_container(iter, DBUS_TYPE_ARRAY,
			DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING
			DBUS_TYPE_STRING_AS_STRING DBUS_TYPE_VARIANT_AS_STRING
			DBUS_DICT_ENTRY_END_CHAR_AS_STRING, &dict);

	uuid = g_strdup(chr->type);
	dict_append_entry(&dict, "UUID", DBUS_TYPE_STRING, &uuid);
	g_free(uuid);


	dict_append_entry(&dict, "Name", DBUS_TYPE_STRING, &name);

	if (chr->desc)
		dict_append_entry(&dict, "Description", DBUS_TYPE_STRING,
								&chr->desc);

	if (chr->value)
		dict_append_array(&dict, "Value", DBUS_TYPE_BYTE, &chr->value,
								chr->vlen);


	dbus_message_iter_close_container(iter, &dict);
}
