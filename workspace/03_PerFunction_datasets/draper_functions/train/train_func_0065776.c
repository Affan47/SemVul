iter_get_fields (DBusMessageIter *iter,
                 gulong attr_type,
                 GckBuilder *builder)
{
	DBusMessageIter array;
	DBusMessageIter dict;
	GString *result;
	const gchar *string;

	g_assert (iter != NULL);
	g_assert (builder != NULL);

	result = g_string_new ("");

	g_return_val_if_fail (dbus_message_iter_get_arg_type (iter) == DBUS_TYPE_ARRAY, FALSE);
	dbus_message_iter_recurse (iter, &array);

	while (dbus_message_iter_get_arg_type (&array) == DBUS_TYPE_DICT_ENTRY) {
		dbus_message_iter_recurse (&array, &dict);


		g_return_val_if_fail (dbus_message_iter_get_arg_type (&dict) == DBUS_TYPE_STRING, FALSE);
		dbus_message_iter_get_basic (&dict, &string);
		g_string_append (result, string);
		g_string_append_c (result, '\0');

		dbus_message_iter_next (&dict);


		g_return_val_if_fail (dbus_message_iter_get_arg_type (&dict) == DBUS_TYPE_STRING, FALSE);
		dbus_message_iter_get_basic (&dict, &string);
		g_string_append (result, string);
		g_string_append_c (result, '\0');

		dbus_message_iter_next (&array);
	}

	gck_builder_add_data (builder, attr_type, (const guchar *)result->str, result->len);
	g_string_free (result, TRUE);
	return TRUE;
}
