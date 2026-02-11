kernel26_cpu_freq_construct (GType object_type, FsoFrameworkSubsystem* subsystem) {
	Kernel26CpuFreq * self = NULL;
	FsoFrameworkSubsystem* _tmp0_ = NULL;
	FsoFrameworkSubsystem* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	gint _tmp3_ = 0;
	gint _tmp5_ = 0;
	FsoFrameworkLogger* _tmp7_ = NULL;
	g_return_val_if_fail (subsystem != NULL, NULL);
	self = (Kernel26CpuFreq*) fso_framework_abstract_object_construct (object_type);
	_tmp0_ = subsystem;
	_tmp1_ = _g_object_ref0 (_tmp0_);
	_g_object_unref0 (self->priv->subsystem);
	self->priv->subsystem = _tmp1_;
	_tmp2_ = default_governor;
	_kernel26_cpu_freq_setGovernor (self, _tmp2_);
	_tmp3_ = max_frequency;
	if (_tmp3_ > 0) {
		gint _tmp4_ = 0;
		_tmp4_ = max_frequency;
		_kernel26_cpu_freq_setFrequency (self, KERNEL26_NODE_NAME_MAX_FREQUENCY, _tmp4_);
	}
	_tmp5_ = min_frequency;
	if (_tmp5_ > 0) {
		gint _tmp6_ = 0;
		_tmp6_ = min_frequency;
		_kernel26_cpu_freq_setFrequency (self, KERNEL26_NODE_NAME_MIN_FREQUENCY, _tmp6_);
	}
	_tmp7_ = ((FsoFrameworkAbstractObject*) self)->logger;
	fso_framework_logger_info (_tmp7_, "Created");
	return self;
}
