gogo_prop_end (GsfXMLIn *xin, G_GNUC_UNUSED GsfXMLBlob *unknown)
{
	GogXMLReadState *state = (GogXMLReadState *)xin->user_state;
	char const *content = xin->content->str;
	GType prop_type, prop_ftype;
	GValue val = { 0 };

	if (state->obj == NULL || state->prop_spec == NULL)
		return;

	prop_type = G_PARAM_SPEC_VALUE_TYPE (state->prop_spec);
	prop_ftype = G_TYPE_FUNDAMENTAL (prop_type);
	if (prop_ftype == G_TYPE_OBJECT) {
		GogObject *obj = state->obj;

		if (!state->prop_pushed_obj)
			return;

		state->obj = state->obj_stack->data;
		state->obj_stack = g_slist_remove (state->obj_stack, state->obj);
		state->prop_pushed_obj = FALSE;

		g_value_init (&val, prop_type);
		g_value_set_object (&val, G_OBJECT (obj));
		g_object_unref (obj);
	} else {
		if (content == NULL && prop_ftype != G_TYPE_BOOLEAN) {
			g_warning ("could not convert NULL to type `%s' for property `%s'",
				   g_type_name (prop_type), state->prop_spec->name);
			return;
		}

		if (!gsf_xml_gvalue_from_str (&val, prop_type, content)) {
			g_warning ("could not convert string to type `%s' for property `%s'",
				   g_type_name (prop_type), state->prop_spec->name);
			return;
		}
	}
	g_object_set_property (G_OBJECT (state->obj),
		state->prop_spec->name, &val);
	g_value_unset (&val);
}
