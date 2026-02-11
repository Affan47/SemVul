od_meta_user_defined_end (GsfXMLIn *xin, G_GNUC_UNUSED GsfXMLBlob *blob)
{
	GsfOOMetaIn *mi = (GsfOOMetaIn *)xin->user_state;

	if (mi->name != NULL) {
		GValue *res = g_new0 (GValue, 1);
		GType t = mi->typ;
		if (t == G_TYPE_NONE) t = G_TYPE_STRING;
		if (gsf_xml_gvalue_from_str (res, t, xin->content->str)) {
			if (g_str_has_prefix (mi->name, "GSF_DOCPROP_VECTOR:")) {
				gchar *true_name = strchr (mi->name + 19, ':');
				if (true_name != NULL && *(++true_name) != 0) {
					GsfDocProp *prop = gsf_doc_meta_data_lookup
						(mi->md, true_name);
					if (prop == NULL) {
						GsfDocPropVector *vector = gsf_docprop_vector_new ();
						GValue *val_vector = g_new0 (GValue, 1);
						g_value_init (val_vector, GSF_DOCPROP_VECTOR_TYPE);
						gsf_docprop_vector_append (vector, res);
						g_value_set_object (val_vector, vector);
						gsf_doc_meta_data_insert (mi->md, g_strdup (true_name),
									  val_vector);
						g_value_unset (res);
						g_free (res);
					} else {
						GValue const *old = gsf_doc_prop_get_val (prop);
						if (G_VALUE_HOLDS (old, GSF_DOCPROP_VECTOR_TYPE)) {
							GValue *new = g_new0 (GValue, 1);
							GValueArray *vector;
							g_value_init (new, GSF_DOCPROP_VECTOR_TYPE);
							g_value_copy (old, new);
							vector = gsf_value_get_docprop_varray (new);
							g_value_array_append (vector, res);
							gsf_doc_prop_set_val (prop, new);
						} else
							g_printerr (_("Property \"%s\" used for "
								      "multiple types!"), true_name);
						g_value_unset (res);
						g_free (res);
					}

					g_free (mi->name);
					mi->name = NULL;
					return;
				}
			}
			gsf_doc_meta_data_insert (mi->md, mi->name, res);
		} else {
			g_free (res);
			g_free (mi->name);
		}
		mi->name = NULL;
	}
}
