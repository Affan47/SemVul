meta_write_props (char const *prop_name, GsfDocProp *prop, GsfXMLOut *output)
{
	char const *mapped_name;
	GValue const *val = gsf_doc_prop_get_val (prop);


	if (0 == strcmp (prop_name, GSF_META_NAME_KEYWORDS)) {
		GValueArray *va;
		unsigned i;
		char *str;


		if (G_TYPE_STRING == G_VALUE_TYPE (val)) {
			str = g_value_dup_string (val);
			if (str && *str) {
				gsf_xml_out_start_element (output, "meta:keyword");
				gsf_xml_out_add_cstr (output, NULL, str);
				gsf_xml_out_end_element (output);
			}
			g_free (str);
		} else if (NULL != (va = gsf_value_get_docprop_varray (val))) {
			for (i = 0 ; i < va->n_values; i++) {
				str = g_value_dup_string (g_value_array_get_nth	(va, i));
				gsf_xml_out_start_element (output, "meta:keyword");
				gsf_xml_out_add_cstr (output, NULL, str);
				gsf_xml_out_end_element (output);
				g_free (str);
			}
		}
		return;
	}

	if (NULL == (mapped_name = od_map_prop_name (prop_name))) {
		if (GSF_DOCPROP_VECTOR_TYPE == G_VALUE_TYPE (val)) {
			GValueArray	 *vector = gsf_value_get_docprop_varray	(val);
			guint		  i;
			guint		  num_values = vector->n_values;

			for (i = 0; i < num_values; i++) {
				GValue	*v;
				char    *new_name = g_strdup_printf
					("GSF_DOCPROP_VECTOR:%.4i:%s", i, prop_name);

				v = g_value_array_get_nth (vector, i);
				meta_write_props_user_defined (new_name, v, output);
				g_free (new_name);
			}
		} else
			meta_write_props_user_defined (prop_name, val, output);
		return;
	}


	gsf_xml_out_start_element (output, mapped_name);
	if (NULL != val)
		gsf_xml_out_add_gvalue_for_odf (output, NULL, val);
	gsf_xml_out_end_element (output);
}
