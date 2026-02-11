gog_object_write_property_sax (GogObject const *obj, GParamSpec *pspec, GsfXMLOut *output)
{
	GObject *val_obj;
	GType    prop_type = G_PARAM_SPEC_VALUE_TYPE (pspec);
	GValue	 value = { 0 };

	g_value_init (&value, prop_type);
	g_object_get_property  (G_OBJECT (obj), pspec->name, &value);


	if (((pspec->flags & GOG_PARAM_POSITION) &&
	     gog_object_is_default_position_flags (obj, pspec->name)) ||
	    (!(pspec->flags & GOG_PARAM_FORCE_SAVE) &&
	     !(pspec->flags & GOG_PARAM_POSITION) &&
	     g_param_value_defaults (pspec, &value))) {
		g_value_unset (&value);
		return;
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
		gsf_xml_out_start_element (output, "property");
		gsf_xml_out_add_cstr_unchecked (output, "name", pspec->name);
		gsf_xml_out_add_cstr (output, NULL, g_value_get_string (&str));
		gsf_xml_out_end_element (output);
		g_value_unset (&str);
		break;
	}

	case G_TYPE_STRING: {
		char const *str = g_value_get_string (&value);
		if (str != NULL) {
			gsf_xml_out_start_element (output, "property");
			gsf_xml_out_add_cstr_unchecked (output, "name", pspec->name);
			gsf_xml_out_add_cstr (output, NULL, str);
			gsf_xml_out_end_element (output);
		}
		break;
	}

	case G_TYPE_OBJECT:
		val_obj = g_value_get_object (&value);
		if (val_obj != NULL) {
			if (GO_IS_PERSIST (val_obj)) {
				gsf_xml_out_start_element (output, "property");
				gsf_xml_out_add_cstr_unchecked (output, "name", pspec->name);
				go_persist_sax_save (GO_PERSIST (val_obj), output);
				gsf_xml_out_end_element (output);
			} else
				g_warning ("How are we supposed to persist this ??");
		}
		break;

	default:
		g_warning ("I could not persist property \"%s\", since type \"%s\" is unhandled.",
			   g_param_spec_get_name (pspec), g_type_name (G_TYPE_FUNDAMENTAL(prop_type)));
	}
	g_value_unset (&value);
}
