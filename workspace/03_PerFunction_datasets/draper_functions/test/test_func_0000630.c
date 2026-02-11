number_to_float_old (Number* self) {
	gfloat result = 0.0F;
	gboolean _tmp0_ = FALSE;
	gfloat z = 0.0F;
	gint i = 0;
	gfloat _tmp10_ = 0.0F;
	gint _tmp11_ = 0;
	gint _tmp12_ = 0;
	gdouble _tmp13_ = 0.0;
	gint _tmp14_ = 0;
	g_return_val_if_fail (self != NULL, 0.0F);
	_tmp0_ = number_is_zero (self);
	if (_tmp0_) {
		result = 0.f;
		return result;
	}
	z = 0.f;
	i = 0;
	{
		gboolean _tmp1_ = FALSE;
		_tmp1_ = TRUE;
		while (TRUE) {
			gboolean _tmp2_ = FALSE;
			gint _tmp4_ = 0;
			gfloat _tmp5_ = 0.0F;
			gint _tmp6_ = 0;
			gint _tmp7_ = 0;
			gfloat _tmp8_ = 0.0F;
			gfloat _tmp9_ = 0.0F;
			_tmp2_ = _tmp1_;
			if (!_tmp2_) {
				gint _tmp3_ = 0;
				_tmp3_ = i;
				i = _tmp3_ + 1;
			}
			_tmp1_ = FALSE;
			_tmp4_ = i;
			if (!(_tmp4_ < T)) {
				break;
			}
			_tmp5_ = z;
			_tmp6_ = i;
			_tmp7_ = self->re_fraction[_tmp6_];
			z = (BASE * _tmp5_) + _tmp7_;
			_tmp8_ = z;
			_tmp9_ = z;
			if ((_tmp8_ + 1.0f) <= _tmp9_) {
				break;
			}
		}
	}
	_tmp10_ = z;
	_tmp11_ = self->re_exponent;
	_tmp12_ = i;
	_tmp13_ = number_mppow_ri (self, (gfloat) BASE, (_tmp11_ - _tmp12_) - 1);
	z = (gfloat) (_tmp10_ * _tmp13_);
	_tmp14_ = self->re_sign;
	if (_tmp14_ < 0) {
		gfloat _tmp15_ = 0.0F;
		_tmp15_ = z;
		result = -_tmp15_;
		return result;
	} else {
		result = z;
		return result;
	}
}
