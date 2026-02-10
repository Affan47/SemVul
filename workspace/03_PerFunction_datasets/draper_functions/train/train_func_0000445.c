gkd_secret_session_set_item_secret (GkdSecretSession *self, GckObject *item,
                                    GkdSecretSecret *secret, DBusError *derr)
{
	GckBuilder builder = GCK_BUILDER_INIT;
	GckMechanism mech;
	GckObject *object;
	GckSession *session;
	GError *error = NULL;
	GckAttributes *attrs;

	g_return_val_if_fail (GKD_SECRET_IS_SESSION (self), FALSE);
	g_return_val_if_fail (GCK_IS_OBJECT (item), FALSE);
	g_return_val_if_fail (secret, FALSE);

	g_assert (GCK_IS_OBJECT (self->key));


	attrs = gck_object_get (item, NULL, &error, CKA_ID, CKA_G_COLLECTION, GCK_INVALID);
	if (attrs == NULL) {
		g_message ("couldn't get item attributes: %s", egg_error_message (error));
		dbus_set_error_const (derr, DBUS_ERROR_FAILED, "Couldn't set item secret");
		g_clear_error (&error);
		return FALSE;
	}
	gck_builder_add_all (&builder, attrs);
	gck_attributes_unref (attrs);
	gck_builder_add_ulong (&builder, CKA_CLASS, CKO_SECRET_KEY);

	session = gkd_secret_service_get_pkcs11_session (self->service, self->caller);
	g_return_val_if_fail (session, FALSE);

	mech.type = self->mech_type;
	mech.parameter = secret->parameter;
	mech.n_parameter = secret->n_parameter;

	object = gck_session_unwrap_key_full (session, self->key, &mech, secret->value,
	                                      secret->n_value, gck_builder_end (&builder), NULL, &error);

	if (object == NULL) {
		if (g_error_matches (error, GCK_ERROR, CKR_USER_NOT_LOGGED_IN)) {
			dbus_set_error_const (derr, SECRET_ERROR_IS_LOCKED,
			                      "Cannot set secret of a locked item");
		} else if (g_error_matches (error, GCK_ERROR, CKR_WRAPPED_KEY_INVALID) ||
		           g_error_matches (error, GCK_ERROR, CKR_WRAPPED_KEY_LEN_RANGE) ||
		           g_error_matches (error, GCK_ERROR, CKR_MECHANISM_PARAM_INVALID)) {
			dbus_set_error_const (derr, DBUS_ERROR_INVALID_ARGS,
			                      "The secret was transferred or encrypted in an invalid way.");
		} else {
			g_message ("couldn't unwrap item secret: %s", egg_error_message (error));
			dbus_set_error_const (derr, DBUS_ERROR_FAILED, "Couldn't set item secret");
		}
		g_clear_error (&error);
		return FALSE;
	}

	if (!gck_object_equal (object, item)) {
		g_warning ("unwrapped secret went to new object, instead of item");
		dbus_set_error_const (derr, DBUS_ERROR_FAILED, "Couldn't set item secret");
		g_object_unref (object);
		return FALSE;
	}

	g_object_unref (object);
	return TRUE;
}
