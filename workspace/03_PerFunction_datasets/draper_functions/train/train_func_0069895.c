multi_term_shell_config_construct (GType object_type, MultiTermConfig* cfg, const gchar* section) {
	MultiTermShellConfig* self = NULL;
	MultiTermConfig* _tmp0_;
	MultiTermConfig* _tmp1_;
	const gchar* _tmp2_;
	gchar* _tmp3_;
	g_return_val_if_fail (cfg != NULL, NULL);
	g_return_val_if_fail (section != NULL, NULL);
	self = (MultiTermShellConfig*) g_type_create_instance (object_type);
	_tmp0_ = cfg;
	_tmp1_ = _multi_term_config_ref0 (_tmp0_);
	_multi_term_config_unref0 (self->_cfg);
	self->_cfg = _tmp1_;
	_tmp2_ = section;
	_tmp3_ = g_strdup (_tmp2_);
	_g_free0 (self->priv->_section);
	self->priv->_section = _tmp3_;
	return self;
}
