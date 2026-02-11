cd_device_remove_profile (CdDevice *device,
			  const gchar *profile_object_path,
			  GError **error)
{
	CdDevicePrivate *priv = device->priv;
	CdDeviceProfileItem *item;
	gboolean ret = FALSE;
	guint i;


	for (i = 0; i < priv->profiles->len; i++) {
		item = g_ptr_array_index (priv->profiles, i);
		if (g_strcmp0 (profile_object_path,
			       cd_profile_get_object_path (item->profile)) == 0) {
			ret = TRUE;
			break;
		}
	}
	if (!ret) {
		g_set_error (error,
			     CD_DEVICE_ERROR,
			     CD_DEVICE_ERROR_PROFILE_DOES_NOT_EXIST,
			     "profile object path '%s' does not exist on '%s'",
			     profile_object_path,
			     priv->object_path);
		goto out;
	}


	ret = g_ptr_array_remove (priv->profiles, item);
	g_assert (ret);


	cd_device_reset_modified (device);


	cd_device_dbus_emit_property_changed (device,
					      "Profiles",
					      cd_device_get_profiles_as_variant (device));


	cd_device_dbus_emit_device_changed (device);
out:
	return ret;
}
