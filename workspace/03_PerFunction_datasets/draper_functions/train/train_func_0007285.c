eap_method_init (gsize obj_size,
                 EMValidateFunc validate,
                 EMAddToSizeGroupFunc add_to_size_group,
                 EMFillConnectionFunc fill_connection,
                 EMUpdateSecretsFunc update_secrets,
                 EMDestroyFunc destroy,
                 const char *ui_file,
                 const char *ui_widget_name,
                 const char *default_field,
                 gboolean phase2)
{
	EAPMethod *method;
	GError *error = NULL;

	g_return_val_if_fail (obj_size > 0, NULL);
	g_return_val_if_fail (ui_file != NULL, NULL);
	g_return_val_if_fail (ui_widget_name != NULL, NULL);

	method = g_slice_alloc0 (obj_size);
	g_assert (method);

	method->refcount = 1;
	method->obj_size = obj_size;
	method->validate = validate;
	method->add_to_size_group = add_to_size_group;
	method->fill_connection = fill_connection;
	method->update_secrets = update_secrets;
	method->destroy = destroy;
	method->default_field = default_field;
	method->phase2 = phase2;

	method->builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (method->builder, ui_file, &error)) {
		g_warning ("Couldn't load UI builder file %s: %s",
		           ui_file, error->message);
		eap_method_unref (method);
		return NULL;
	}

	method->ui_widget = GTK_WIDGET (gtk_builder_get_object (method->builder, ui_widget_name));
	if (!method->ui_widget) {
		g_warning ("Couldn't load UI widget '%s' from UI file %s",
		           ui_widget_name, ui_file);
		eap_method_unref (method);
		return NULL;
	}
	g_object_ref_sink (method->ui_widget);

	return method;
}
