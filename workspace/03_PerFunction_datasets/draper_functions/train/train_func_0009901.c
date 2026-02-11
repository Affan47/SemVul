_go_component_start (GsfXMLIn *xin, xmlChar const **attrs)
{
	GOCompXMLReadState *state = (GOCompXMLReadState *) xin->user_state;
	char const *mime_type = NULL;
	int i;
	double width = 1., height = 1.;

	for (i = 0; attrs != NULL && attrs[i] && attrs[i+1] ; i += 2)
		if (0 == strcmp (attrs[i], "mime-type"))
			mime_type = (char const *) attrs[i+1];
		else if (0 == strcmp (attrs[i], "width"))
			width = go_ascii_strtod ((char const *) attrs[i+1], NULL);
		else if (0 == strcmp (attrs[i], "height"))
			height = go_ascii_strtod ((char const *) attrs[i+1], NULL);

	g_return_if_fail (mime_type);
	state->component = go_component_new_by_mime_type (mime_type);
	if (!state->component) {
		state->component = g_object_new (go_component_snapshot_get_type (), NULL);
		state->component->mime_type = g_strdup (mime_type);
		state->component->width = width;
		state->component->height = height;
	} else for (i = 0; attrs != NULL && attrs[i] && attrs[i+1] ; i += 2) {
		GParamSpec *prop_spec;
		GValue res;
		memset (&res, 0, sizeof (res));
		prop_spec = g_object_class_find_property (
				G_OBJECT_GET_CLASS (state->component), attrs[i]);
		if (prop_spec && (prop_spec->flags & GO_PARAM_PERSISTENT) &&
			gsf_xml_gvalue_from_str (&res,
				G_TYPE_FUNDAMENTAL (G_PARAM_SPEC_VALUE_TYPE (prop_spec)),
				attrs[i+1])) {
			g_object_set_property (G_OBJECT (state->component), attrs[i], &res);
			g_value_unset (&res);
		}
	}

}
