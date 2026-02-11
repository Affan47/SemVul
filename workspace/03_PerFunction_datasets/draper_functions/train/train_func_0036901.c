folks_abstract_field_details_real_set_parameters (FolksAbstractFieldDetails* base, GeeMultiMap* value) {
	FolksAbstractFieldDetails* self;
	GeeMultiMap* _tmp0_ = NULL;
	self = base;
	_tmp0_ = value;
	if (_tmp0_ == NULL) {
		GeeMultiMap* _tmp1_ = NULL;
		_tmp1_ = self->priv->_parameters;
		gee_multi_map_clear (_tmp1_);
	} else {
		GeeMultiMap* _tmp2_ = NULL;
		GeeMultiMap* _tmp3_ = NULL;
		_tmp2_ = value;
		_tmp3_ = _g_object_ref0 (_tmp2_);
		_g_object_unref0 (self->priv->_parameters);
		self->priv->_parameters = _tmp3_;
	}
	g_object_notify ((GObject *) self, "parameters");
}
