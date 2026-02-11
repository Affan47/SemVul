folks_inspect_utils_transform_value_to_string (GValue* prop_value) {
	gchar* result = NULL;
	GType _tmp0_ = 0UL;
	gboolean _tmp1_ = FALSE;
	g_return_val_if_fail (prop_value != NULL, NULL);
	_tmp0_ = G_VALUE_TYPE (prop_value);
	_tmp1_ = g_value_type_transformable (_tmp0_, G_TYPE_STRING);
	if (_tmp1_) {
		GValue string_value = {0};
		GValue _tmp2_ = {0};
		const gchar* _tmp3_ = NULL;
		gchar* _tmp4_ = NULL;
		g_value_init (&_tmp2_, G_TYPE_STRING);
		string_value = _tmp2_;
		g_value_transform (prop_value, &string_value);
		_tmp3_ = g_value_get_string (&string_value);
		_tmp4_ = g_strdup (_tmp3_);
		result = _tmp4_;
		G_IS_VALUE (&string_value) ? (g_value_unset (&string_value), NULL) : NULL;
		return result;
	} else {
		GType _tmp5_ = 0UL;
		const gchar* _tmp6_ = NULL;
		const gchar* _tmp7_ = NULL;
		gchar* _tmp8_ = NULL;
		_tmp5_ = G_VALUE_TYPE (prop_value);
		_tmp6_ = g_type_name (_tmp5_);
		_tmp7_ = g_type_name (G_TYPE_STRING);
		_tmp8_ = g_strdup_printf ("Can't convert from type '%s' to '%s'", _tmp6_, _tmp7_);
		result = _tmp8_;
		return result;
	}
}
