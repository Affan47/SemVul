nm_setting_to_string (NMSetting *setting)
{
	GString *string;
	GParamSpec **property_specs;
	guint n_property_specs;
	guint i;

	g_return_val_if_fail (NM_IS_SETTING (setting), NULL);

	property_specs = g_object_class_list_properties (G_OBJECT_GET_CLASS (setting), &n_property_specs);
	if (!property_specs)
		return NULL;

	string = g_string_new (nm_setting_get_name (setting));
	g_string_append_c (string, '\n');

	for (i = 0; i < n_property_specs; i++) {
		GParamSpec *prop_spec = property_specs[i];
		GValue value = { 0 };
		char *value_str;
		gboolean is_serializable;
		gboolean is_default;

		g_value_init (&value, prop_spec->value_type);
		g_object_get_property (G_OBJECT (setting), prop_spec->name, &value);

		value_str = g_strdup_value_contents (&value);
		g_string_append_printf (string, "\t%s : %s", prop_spec->name, value_str);
		g_free (value_str);

		is_serializable = prop_spec->flags & NM_SETTING_PARAM_SERIALIZE;
		is_default = g_param_value_defaults (prop_spec, &value);

		g_value_unset (&value);

		if (is_serializable || is_default) {
			g_string_append (string, " (");

			if (is_serializable)
				g_string_append_c (string, 's');
			if (is_default)
				g_string_append_c (string, 'd');

			g_string_append_c (string, ')');
		}

		g_string_append_c (string, '\n');
	}

	g_free (property_specs);
	g_string_append_c (string, '\n');

	return g_string_free (string, FALSE);
}
