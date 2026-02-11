___lambda3_ (Block2Data* _data2_) {
	Block1Data* _data1_;
	UsageResource * self;
	gboolean result = FALSE;
	gint _tmp0_ = 0;
	FreeSmartphoneResource* _tmp7_ = NULL;
	gint _tmp15_ = 0;
	_data1_ = _data2_->_data1_;
	self = _data1_->self;
	_tmp0_ = _data2_->retries;
	if (_tmp0_ > 10) {
		UsageController* _tmp1_ = NULL;
		FsoFrameworkLogger* _tmp2_ = NULL;
		const gchar* _tmp3_ = NULL;
		const gchar* _tmp4_ = NULL;
		gchar* _tmp5_ = NULL;
		gchar* _tmp6_ = NULL;
		_tmp1_ = usage_instance;
		_tmp2_ = ((FsoFrameworkAbstractObject*) _tmp1_)->logger;
		_tmp3_ = self->priv->_name;
		_tmp4_ = string_to_string (_tmp3_);
		_tmp5_ = g_strconcat ("Can't enable resource '", _tmp4_, "' as it has never registered!", NULL);
		_tmp6_ = _tmp5_;
		fso_framework_logger_error (_tmp2_, _tmp6_);
		_g_free0 (_tmp6_);
		result = FALSE;
		return result;
	}
	_tmp7_ = self->proxy;
	if (_tmp7_ != NULL) {
		UsageController* _tmp8_ = NULL;
		FsoFrameworkLogger* _tmp9_ = NULL;
		const gchar* _tmp10_ = NULL;
		const gchar* _tmp11_ = NULL;
		gchar* _tmp12_ = NULL;
		gchar* _tmp13_ = NULL;
		gboolean _tmp14_ = FALSE;
		_tmp8_ = usage_instance;
		_tmp9_ = ((FsoFrameworkAbstractObject*) _tmp8_)->logger;
		_tmp10_ = self->priv->_name;
		_tmp11_ = string_to_string (_tmp10_);
		_tmp12_ = g_strconcat ("DBus proxy for resource '", _tmp11_, "' is now available.", NULL);
		_tmp13_ = _tmp12_;
		_tmp14_ = fso_framework_logger_debug (_tmp9_, _tmp13_);
		_vala_assert (_tmp14_, "instance.logger.debug( @\"DBus proxy for resource '$name' is now available.\" )");
		_g_free0 (_tmp13_);
		usage_resource_real_enable_co (_data1_->_async_data_);
		result = FALSE;
		return result;
	}
	_tmp15_ = _data2_->retries;
	_data2_->retries = _tmp15_ + 1;
	result = TRUE;
	return result;
}
