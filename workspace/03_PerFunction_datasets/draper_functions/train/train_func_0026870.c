click_app_hook_real_compare_to (GeeComparable* base, ClickAppHook* obj) {
	ClickAppHook * self;
	gint result = 0;
	gint ret = 0;
	GCompareFunc _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	ClickAppHook* _tmp2_ = NULL;
	const gchar* _tmp3_ = NULL;
	gint _tmp4_ = 0;
	gint _tmp5_ = 0;
	GCompareFunc _tmp6_ = NULL;
	const gchar* _tmp7_ = NULL;
	ClickAppHook* _tmp8_ = NULL;
	const gchar* _tmp9_ = NULL;
	gint _tmp10_ = 0;
	self = (ClickAppHook*) base;
	g_return_val_if_fail (obj != NULL, 0);
	_tmp0_ = g_strcmp0;
	_tmp1_ = self->priv->_app_name;
	_tmp2_ = obj;
	_tmp3_ = _tmp2_->priv->_app_name;
	_tmp4_ = _tmp0_ (_tmp1_, _tmp3_);
	ret = _tmp4_;
	_tmp5_ = ret;
	if (_tmp5_ != 0) {
		result = ret;
		return result;
	}
	_tmp6_ = g_strcmp0;
	_tmp7_ = self->priv->_hook_name;
	_tmp8_ = obj;
	_tmp9_ = _tmp8_->priv->_hook_name;
	_tmp10_ = _tmp6_ (_tmp7_, _tmp9_);
	result = _tmp10_;
	return result;
}
