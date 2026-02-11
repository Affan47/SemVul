math_converter_set_category (MathConverter* self, const gchar* category) {
	const gchar* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	gchar* _tmp3_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->category;
	_tmp1_ = category;
	if (g_strcmp0 (_tmp0_, _tmp1_) == 0) {
		return;
	}
	_tmp2_ = category;
	_tmp3_ = g_strdup (_tmp2_);
	_g_free0 (self->priv->category);
	self->priv->category = _tmp3_;
	math_converter_update_from_model (self);
}
