gkd_secret_objects_append_collection_paths (GkdSecretObjects *self,
                                            DBusMessageIter *iter,
                                            DBusMessage *message)
{
	DBusMessageIter variant;
	DBusMessageIter array;

	g_return_if_fail (GKD_SECRET_IS_OBJECTS (self));
	g_return_if_fail (iter != NULL);

	dbus_message_iter_open_container (iter, DBUS_TYPE_VARIANT, "ao", &variant);
	dbus_message_iter_open_container (&variant, DBUS_TYPE_ARRAY, "o", &array);

	gkd_secret_objects_foreach_collection (self, message, on_object_path_append_to_iter, &array);

	dbus_message_iter_close_container (&variant, &array);
	dbus_message_iter_close_container (iter, &variant);
}
