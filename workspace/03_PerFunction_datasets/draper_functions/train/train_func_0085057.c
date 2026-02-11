string_fields_to_template_va (va_list args, const gchar *name,
                              GArray *template)
{
	GString *fields = g_string_sized_new (128);
	const gchar *last = NULL;
	gint cmp;

	g_assert (name);
	g_assert (template);

	while (name != NULL) {
		g_string_append (fields, name);
		g_string_append_c (fields, '\0');
		g_string_append (fields, va_arg (args, const gchar*));
		g_string_append_c (fields, '\0');


		if (name && last) {
			cmp = strcmp (last, name);
			if (cmp == 0)
				g_warning ("duplicate names in attributes not allowed: %s %s", last, name);
			else if (cmp > 0)
				g_warning ("names in attributes must in alphabetical order: %s %s", last, name);
		}

		last = name;
		name = va_arg (args, const gchar*);
	}

	gkm_template_set_value (template, CKA_G_FIELDS, fields->str, fields->len);
	g_string_free (fields, TRUE);
}
