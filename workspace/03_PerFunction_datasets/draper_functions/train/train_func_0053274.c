kernel26_aggregate_power_supply_getCapacity (Kernel26AggregatePowerSupply* self) {
	gint result = 0;
	gint amount = 0;
	gint numValues = 0;
	GList* _tmp0_ = NULL;
	gint _tmp8_ = 0;
	gint _tmp9_ = 0;
	gint _tmp12_ = 0;
	g_return_val_if_fail (self != NULL, 0);
	amount = -1;
	numValues = 0;
	_tmp0_ = instances;
	{
		GList* supply_collection = NULL;
		GList* supply_it = NULL;
		supply_collection = _tmp0_;
		for (supply_it = supply_collection; supply_it != NULL; supply_it = supply_it->next) {
			Kernel26PowerSupply* _tmp1_ = NULL;
			Kernel26PowerSupply* supply = NULL;
			_tmp1_ = _g_object_ref0 ((Kernel26PowerSupply*) supply_it->data);
			supply = _tmp1_;
			{
				gint v = 0;
				Kernel26PowerSupply* _tmp2_ = NULL;
				gint _tmp3_ = 0;
				gint _tmp4_ = 0;
				_tmp2_ = supply;
				_tmp3_ = kernel26_power_supply_getCapacity (_tmp2_);
				v = _tmp3_;
				_tmp4_ = v;
				if (_tmp4_ != (-1)) {
					gint _tmp5_ = 0;
					gint _tmp6_ = 0;
					gint _tmp7_ = 0;
					_tmp5_ = amount;
					_tmp6_ = v;
					amount = _tmp5_ + _tmp6_;
					_tmp7_ = numValues;
					numValues = _tmp7_ + 1;
				}
				_g_object_unref0 (supply);
			}
		}
	}
	_tmp9_ = numValues;
	if (_tmp9_ > 0) {
		gint _tmp10_ = 0;
		gint _tmp11_ = 0;
		_tmp10_ = amount;
		_tmp11_ = numValues;
		_tmp8_ = _tmp10_ / _tmp11_;
	} else {
		_tmp8_ = -1;
	}
	_tmp12_ = _tmp8_;
	result = _tmp12_;
	return result;
}
