go_distribution_persist_sax_save (GOPersist const *gp, GsfXMLOut *output)
{
	GODistribution const *dist = GO_DISTRIBUTION (gp);
	GParamSpec **props;
	int n;

	g_return_if_fail (dist);
	gsf_xml_out_add_cstr_unchecked (output, "type",
		G_OBJECT_TYPE_NAME (dist));

	if (dist->location != 0.)
		gsf_xml_out_add_float (output, "location", dist->location, -1);
	if (dist->scale != 1.)
		gsf_xml_out_add_float (output, "scale", dist->scale, -1);


	props = g_object_class_list_properties (G_OBJECT_GET_CLASS (dist), &n);
	while (n-- > 0)
		if (props[n]->flags & GO_PARAM_PERSISTENT) {
			GType    prop_type = G_PARAM_SPEC_VALUE_TYPE (props[n]);
			GValue	 value = { 0 };

			g_value_init (&value, prop_type);
			g_object_get_property  (G_OBJECT (dist), props[n]->name, &value);


			if (g_param_value_defaults (props[n], &value)) {
				g_value_unset (&value);
				continue;
			}

			switch (G_TYPE_FUNDAMENTAL (prop_type)) {
			case G_TYPE_CHAR:
			case G_TYPE_UCHAR:
			case G_TYPE_BOOLEAN:
			case G_TYPE_INT:
			case G_TYPE_UINT:
			case G_TYPE_LONG:
			case G_TYPE_ULONG:
			case G_TYPE_FLOAT:
			case G_TYPE_DOUBLE:
			case G_TYPE_ENUM:
			case G_TYPE_FLAGS: {
				GValue str = { 0 };
				g_value_init (&str, G_TYPE_STRING);
				g_value_transform (&value, &str);
				gsf_xml_out_add_cstr (output, props[n]->name, g_value_get_string (&str));
				g_value_unset (&str);
				break;
			}

			case G_TYPE_STRING: {
				char const *str = g_value_get_string (&value);
				if (str != NULL) {
					gsf_xml_out_add_cstr (output,  props[n]->name, str);
				}
				break;
			}

			default:
				g_warning ("I could not persist property \"%s\", since type \"%s\" is unhandled.",
					   g_param_spec_get_name (props[n]), g_type_name (G_TYPE_FUNDAMENTAL(prop_type)));
			}
			g_value_unset (&value);
		}
}
