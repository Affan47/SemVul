kernel26_aggregate_power_supply_sendCapacityIfChanged (Kernel26AggregatePowerSupply* self, gint energy) {
	gint _tmp0_ = 0;
	gint _tmp1_ = 0;
	gint _tmp2_ = 0;
	gint _tmp3_ = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->energy;
	_tmp1_ = energy;
	if (_tmp0_ == _tmp1_) {
		return;
	}
	_tmp2_ = energy;
	self->priv->energy = _tmp2_;
	_tmp3_ = energy;
	g_signal_emit_by_name ((FreeSmartphoneDevicePowerSupply*) self, "capacity", _tmp3_);
}
