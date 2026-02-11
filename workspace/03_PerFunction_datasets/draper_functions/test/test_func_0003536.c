fso_framework_combined_transport_real_isOpen (FsoFrameworkTransport* base) {
	FsoFrameworkCombinedTransport * self;
	gboolean result = FALSE;
	gboolean _tmp0_ = FALSE;
	FsoFrameworkTransport* _tmp1_ = NULL;
	gboolean _tmp2_ = FALSE;
	gboolean _tmp5_ = FALSE;
	self = (FsoFrameworkCombinedTransport*) base;
	_tmp1_ = self->priv->_rwtransport;
	_tmp2_ = fso_framework_transport_isOpen (_tmp1_);
	if (_tmp2_) {
		FsoFrameworkTransport* _tmp3_ = NULL;
		gboolean _tmp4_ = FALSE;
		_tmp3_ = self->priv->_rotransport;
		_tmp4_ = fso_framework_transport_isOpen (_tmp3_);
		_tmp0_ = _tmp4_;
	} else {
		_tmp0_ = FALSE;
	}
	_tmp5_ = _tmp0_;
	result = _tmp5_;
	return result;
}
