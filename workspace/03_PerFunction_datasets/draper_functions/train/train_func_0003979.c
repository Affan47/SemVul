unity_protocol_filter_definition_add_option (UnityProtocolFilterDefinition* self, const gchar* id, const gchar* name) {
	const gchar* _tmp0_ = NULL;
	gchar _tmp1_ = '\0';
	gchar** _tmp2_ = NULL;
	gint _tmp2__length1 = 0;
	const gchar* _tmp3_ = NULL;
	gchar* _tmp4_ = NULL;
	gchar** _tmp5_ = NULL;
	gint _tmp5__length1 = 0;
	const gchar* _tmp6_ = NULL;
	gchar* _tmp7_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (id != NULL);
	g_return_if_fail (name != NULL);
	_tmp0_ = id;
	_tmp1_ = string_get (_tmp0_, (glong) 0);
	g_return_if_fail (_tmp1_ != '\0');
	_tmp2_ = self->priv->option_ids;
	_tmp2__length1 = self->priv->option_ids_length1;
	_tmp3_ = id;
	_tmp4_ = g_strdup (_tmp3_);
	_vala_array_add5 (&self->priv->option_ids, &self->priv->option_ids_length1, &self->priv->_option_ids_size_, _tmp4_);
	_tmp5_ = self->priv->option_names;
	_tmp5__length1 = self->priv->option_names_length1;
	_tmp6_ = name;
	_tmp7_ = g_strdup (_tmp6_);
	_vala_array_add6 (&self->priv->option_names, &self->priv->option_names_length1, &self->priv->_option_names_size_, _tmp7_);
}
