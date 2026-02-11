alm_param_spec_app_choose_info (const gchar* name, const gchar* nick, const gchar* blurb, GType object_type, GParamFlags flags) {
	AlmParamSpecAppChooseInfo* spec;
	g_return_val_if_fail (g_type_is_a (object_type, ALM_TYPE_APP_CHOOSE_INFO), NULL);
	spec = g_param_spec_internal (G_TYPE_PARAM_OBJECT, name, nick, blurb, flags);
	G_PARAM_SPEC (spec)->value_type = object_type;
	return G_PARAM_SPEC (spec);
}
