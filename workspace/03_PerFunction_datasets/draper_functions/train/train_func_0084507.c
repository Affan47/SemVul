gkd_secret_create_encode_result (GkdSecretPrompt *base, DBusMessageIter *iter)
{
	GkdSecretCreate *self = GKD_SECRET_CREATE (base);
	DBusMessageIter variant;
	const gchar *path;

	dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "o", &variant);
	path = self->result_path ? self->result_path : "/";
	dbus_message_iter_append_basic (&variant, DBUS_TYPE_OBJECT_PATH, &path);
	dbus_message_iter_close_container (iter, &variant);
}
