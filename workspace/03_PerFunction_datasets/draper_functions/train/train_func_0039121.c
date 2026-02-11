e_binding_transform_string_to_color (GBinding *binding,
                                     const GValue *source_value,
                                     GValue *target_value,
                                     gpointer not_used)
{
	GdkColor color;
	const gchar *string;
	gboolean success = FALSE;

	g_return_val_if_fail (G_IS_BINDING (binding), FALSE);

	string = g_value_get_string (source_value);
	if (gdk_color_parse (string, &color)) {
		g_value_set_boxed (target_value, &color);
		success = TRUE;
	}

	return success;
}
