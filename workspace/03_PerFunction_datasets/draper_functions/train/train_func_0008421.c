wireless_security_init (gsize obj_size,
                        WSValidateFunc validate,
                        WSAddToSizeGroupFunc add_to_size_group,
                        WSFillConnectionFunc fill_connection,
                        WSUpdateSecretsFunc update_secrets,
                        WSDestroyFunc destroy,
                        const char *ui_file,
                        const char *ui_widget_name,
                        const char *default_field)
{
	WirelessSecurity *sec;
	GError *error = NULL;

	g_return_val_if_fail (obj_size > 0, NULL);
	g_return_val_if_fail (ui_file != NULL, NULL);
	g_return_val_if_fail (ui_widget_name != NULL, NULL);

	sec = g_slice_alloc0 (obj_size);
	g_assert (sec);

	sec->refcount = 1;
	sec->obj_size = obj_size;

	sec->validate = validate;
	sec->add_to_size_group = add_to_size_group;
	sec->fill_connection = fill_connection;
	sec->update_secrets = update_secrets;
	sec->destroy = destroy;
	sec->default_field = default_field;

	sec->builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (sec->builder, ui_file, &error)) {
		g_warning ("Couldn't load UI builder file %s: %s",
		           ui_file, error->message);
		g_error_free (error);
		wireless_security_unref (sec);
		return NULL;
	}

	sec->ui_widget = GTK_WIDGET (gtk_builder_get_object (sec->builder, ui_widget_name));
	if (!sec->ui_widget) {
		g_warning ("Couldn't load UI widget '%s' from UI file %s",
		           ui_widget_name, ui_file);
		wireless_security_unref (sec);
		return NULL;
	}
	g_object_ref_sink (sec->ui_widget);

	sec->adhoc_compatible = TRUE;

	return sec;
}
