gkd_secret_lock (GckObject *collection, DBusError *derr)
{
	GckBuilder builder = GCK_BUILDER_INIT;
	GError *error = NULL;
	GList *objects, *l;
	GckSession *session;

	gck_builder_add_ulong (&builder, CKA_CLASS, CKO_G_CREDENTIAL);
	gck_builder_add_ulong (&builder, CKA_G_OBJECT, gck_object_get_handle (collection));

	session = gck_object_get_session (collection);
	g_return_val_if_fail (session, FALSE);

	objects = gck_session_find_objects (session, gck_builder_end (&builder), NULL, &error);

	g_object_unref (session);

	if (error != NULL) {
		g_warning ("couldn't search for credential objects: %s", egg_error_message (error));
		dbus_set_error (derr, DBUS_ERROR_FAILED, "Couldn't lock collection");
		g_clear_error (&error);
		return FALSE;
	}

	for (l = objects; l; l = g_list_next (l)) {
		if (!gck_object_destroy (l->data, NULL, &error)) {
			g_warning ("couldn't destroy credential object: %s", egg_error_message (error));
			g_clear_error (&error);
		}
	}

	gck_list_unref_free (objects);
	return TRUE;
}
