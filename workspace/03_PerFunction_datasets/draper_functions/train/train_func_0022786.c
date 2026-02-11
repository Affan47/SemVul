number_construct_eulers (GType object_type) {
	Number* self = NULL;
	Number* z = NULL;
	Number* _tmp0_ = NULL;
	Number* _tmp1_ = NULL;
	Number* _tmp2_ = NULL;
	Number* _tmp3_ = NULL;
	Number* _tmp4_ = NULL;
	gint _tmp5_ = 0;
	Number* _tmp6_ = NULL;
	gint _tmp7_ = 0;
	Number* _tmp8_ = NULL;
	gint _tmp9_ = 0;
	Number* _tmp10_ = NULL;
	gint _tmp11_ = 0;
	self = (Number*) g_type_create_instance (object_type);
	_tmp0_ = number_new_integer ((gint64) 1);
	_tmp1_ = _tmp0_;
	_tmp2_ = number_epowy (_tmp1_);
	_tmp3_ = _tmp2_;
	_number_unref0 (_tmp1_);
	z = _tmp3_;
	_tmp4_ = z;
	_tmp5_ = _tmp4_->re_sign;
	self->re_sign = _tmp5_;
	_tmp6_ = z;
	_tmp7_ = _tmp6_->im_sign;
	self->im_sign = _tmp7_;
	_tmp8_ = z;
	_tmp9_ = _tmp8_->re_exponent;
	self->re_exponent = _tmp9_;
	_tmp10_ = z;
	_tmp11_ = _tmp10_->im_exponent;
	self->im_exponent = _tmp11_;
	{
		gint i = 0;
		i = 0;
		{
			gboolean _tmp12_ = FALSE;
			_tmp12_ = TRUE;
			while (TRUE) {
				gboolean _tmp13_ = FALSE;
				gint _tmp15_ = 0;
				Number* _tmp16_ = NULL;
				gint _tmp17_ = 0;
				Number* _tmp18_ = NULL;
				gint _tmp19_ = 0;
				gint _tmp20_ = 0;
				gint _tmp21_ = 0;
				gint _tmp22_ = 0;
				Number* _tmp23_ = NULL;
				gint _tmp24_ = 0;
				gint _tmp25_ = 0;
				gint _tmp26_ = 0;
				_tmp13_ = _tmp12_;
				if (!_tmp13_) {
					gint _tmp14_ = 0;
					_tmp14_ = i;
					i = _tmp14_ + 1;
				}
				_tmp12_ = FALSE;
				_tmp15_ = i;
				_tmp16_ = z;
				if (!(_tmp15_ < 1000)) {
					break;
				}
				_tmp17_ = i;
				_tmp18_ = z;
				_tmp19_ = i;
				_tmp20_ = _tmp18_->re_fraction[_tmp19_];
				self->re_fraction[_tmp17_] = _tmp20_;
				_tmp21_ = self->re_fraction[_tmp17_];
				_tmp22_ = i;
				_tmp23_ = z;
				_tmp24_ = i;
				_tmp25_ = _tmp23_->im_fraction[_tmp24_];
				self->im_fraction[_tmp22_] = _tmp25_;
				_tmp26_ = self->im_fraction[_tmp22_];
			}
		}
	}
	_number_unref0 (z);
	return self;
}
