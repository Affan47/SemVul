list_item_ids_foreach (DBusMessageIter *iter, gpointer data)
{
	GList **ids = data;
	const char *path;
	guint32 id;

	if (dbus_message_iter_get_arg_type (iter) != DBUS_TYPE_OBJECT_PATH)
		return FALSE;


	dbus_message_iter_get_basic (iter, &path);
	if (gkr_decode_item_id (path, &id))
		*ids = g_list_prepend (*ids, GUINT_TO_POINTER (id));
	else
		g_message ("unsupported item. identifier is not an integer: %s", path);

	return TRUE;
}
