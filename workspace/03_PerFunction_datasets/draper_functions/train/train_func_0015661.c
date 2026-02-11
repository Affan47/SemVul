service_method_lock (GkdSecretService *self, DBusMessage *message)
{
	DBusMessage *reply;
	const char *caller;
	const gchar *prompt;
	GckObject *collection;
	int n_objpaths, i;
	char **objpaths;
	GPtrArray *array;

	if (!dbus_message_get_args (message, NULL,
	                            DBUS_TYPE_ARRAY, DBUS_TYPE_OBJECT_PATH, &objpaths, &n_objpaths,
	                            DBUS_TYPE_INVALID))
		return NULL;

	caller = dbus_message_get_sender (message);
	array = g_ptr_array_new ();
	for (i = 0; i < n_objpaths; ++i) {
		collection = gkd_secret_objects_lookup_collection (self->objects, caller, objpaths[i]);
		if (collection != NULL) {
			if (gkd_secret_lock (collection, NULL)) {
				g_ptr_array_add (array, objpaths[i]);
				gkd_secret_objects_emit_collection_locked (self->objects,
				                                           collection);
			}
			g_object_unref (collection);
		}
	}

	prompt = "/";
	reply = dbus_message_new_method_return (message);
	dbus_message_append_args (reply,
	                          DBUS_TYPE_ARRAY, DBUS_TYPE_OBJECT_PATH, &array->pdata, array->len,
	                          DBUS_TYPE_OBJECT_PATH, &prompt,
	                          DBUS_TYPE_INVALID);

	dbus_free_string_array (objpaths);
	return reply;
}
