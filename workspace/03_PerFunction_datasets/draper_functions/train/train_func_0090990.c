parameter_holder_save_string(ParameterHolder *self) {


    gchar* joined;
    gchar** lines;
    guint n_properties;
    GParamSpec** properties;
    int i, n_lines;
    GValue val, strval;


    properties = g_object_class_list_properties(G_OBJECT_GET_CLASS(self), &n_properties);
    lines = g_malloc0(sizeof(lines[0]) * (n_properties+1));


    n_lines = 0;
    for (i=0; i<n_properties; i++) {


	if (properties[i]->flags & PARAM_SERIALIZED) {

	    memset(&val, 0, sizeof(val));
	    g_value_init(&val, properties[i]->value_type);
	    g_object_get_property(G_OBJECT(self), properties[i]->name, &val);

	    if (!g_param_value_defaults(properties[i], &val)) {


		memset(&strval, 0, sizeof(strval));
		g_value_init(&strval, G_TYPE_STRING);
		g_value_transform(&val, &strval);
		lines[n_lines++] = g_strdup_printf("%s = %s", properties[i]->name, g_value_get_string(&strval));
		g_value_unset(&strval);

	    }
	    g_value_unset(&val);
	}
    }

    lines[n_lines] = NULL;
    joined = g_strjoinv("\n", lines);

    g_free(properties);
    g_strfreev(lines);

    return joined;
}
