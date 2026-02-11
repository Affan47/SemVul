fso_device_base_power_control_construct (GType object_type, const gchar* powernode, const gchar* onvalue, const gchar* offvalue, guint switchtimeout) {
	FsoDeviceBasePowerControl * self = NULL;
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	gchar* _tmp3_ = NULL;
	const gchar* _tmp4_ = NULL;
	gchar* _tmp5_ = NULL;
	guint _tmp6_ = 0U;
	g_return_val_if_fail (onvalue != NULL, NULL);
	g_return_val_if_fail (offvalue != NULL, NULL);
	self = (FsoDeviceBasePowerControl*) fso_framework_abstract_object_construct (object_type);
	_tmp0_ = powernode;
	_tmp1_ = g_strdup (_tmp0_);
	_g_free0 (self->priv->powernode);
	self->priv->powernode = _tmp1_;
	_tmp2_ = onvalue;
	_tmp3_ = g_strdup (_tmp2_);
	_g_free0 (self->priv->onvalue);
	self->priv->onvalue = _tmp3_;
	_tmp4_ = offvalue;
	_tmp5_ = g_strdup (_tmp4_);
	_g_free0 (self->priv->offvalue);
	self->priv->offvalue = _tmp5_;
	_tmp6_ = switchtimeout;
	self->priv->switchtimeout = _tmp6_;
	return self;
}
