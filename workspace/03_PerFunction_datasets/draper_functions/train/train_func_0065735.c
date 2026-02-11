append_class_name (GString *res, MonoClass *class, gboolean include_namespace)
{
	if (!class) {
		g_string_append (res, "Unknown");
		return;
	}
	if (class->nested_in) {
		append_class_name (res, class->nested_in, include_namespace);
		g_string_append_c (res, '/');
	}
	if (include_namespace && *(class->name_space))
		g_string_append_printf (res, "%s.", class->name_space);
	g_string_append_printf (res, "%s", class->name);
}
