tethering_append(DBusMessageIter *iter, void *user_data)
{
	struct tethering_info *tethering = user_data;
	const char *nap = "nap";

	dbus_message_iter_append_basic(iter, DBUS_TYPE_STRING, &nap);
	if (tethering->enable == TRUE)
		dbus_message_iter_append_basic(iter, DBUS_TYPE_STRING,
				&tethering->bridge);
}
