fso_framework_kernel26_module_unload (FsoFrameworkKernel26Module* self) {
	gboolean result = FALSE;
	gboolean _result_ = FALSE;
	gboolean _tmp0_ = FALSE;
	gboolean _tmp1_ = FALSE;
	gboolean _tmp3_ = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	_result_ = FALSE;
	_tmp1_ = self->priv->_available;
	if (_tmp1_) {
		gboolean _tmp2_ = FALSE;
		_tmp2_ = self->priv->_active;
		_tmp0_ = _tmp2_;
	} else {
		_tmp0_ = FALSE;
	}
	_tmp3_ = _tmp0_;
	if (_tmp3_) {
		gint rc = 0;
		const gchar* _tmp4_ = NULL;
		const gchar* _tmp5_ = NULL;
		const gchar* _tmp6_ = NULL;
		gchar* _tmp7_ = NULL;
		gchar* _tmp8_ = NULL;
		gint _tmp9_ = 0;
		gint _tmp10_ = 0;
		gint _tmp11_ = 0;
		_tmp4_ = fso_framework_kernel26_module_get_name (self);
		_tmp5_ = _tmp4_;
		_tmp6_ = string_to_string (_tmp5_);
		_tmp7_ = g_strconcat ("/sbin/modprobe -r ", _tmp6_, NULL);
		_tmp8_ = _tmp7_;
		_tmp9_ = system (_tmp8_);
		_tmp10_ = _tmp9_;
		_g_free0 (_tmp8_);
		rc = _tmp10_;
		_tmp11_ = rc;
		_result_ = _tmp11_ == 0;
		fso_framework_kernel26_module_set_active (self, FALSE);
	}
	result = _result_;
	return result;
}
