umockdev_script_runner_hamming (guint8* d1, int d1_length1, guint8* d2, int d2_length1) {
	guint result = 0U;
	guint8* _tmp0_ = NULL;
	gint _tmp0__length1 = 0;
	guint8* _tmp1_ = NULL;
	gint _tmp1__length1 = 0;
	guint d = 0U;
	guint i = 0U;
	_tmp0_ = d1;
	_tmp0__length1 = d1_length1;
	_tmp1_ = d2;
	_tmp1__length1 = d2_length1;
	_vala_assert (_tmp0__length1 == _tmp1__length1, "d1.length == d2.length");
	d = (guint) 0;
	{
		gboolean _tmp2_ = FALSE;
		i = (guint) 0;
		_tmp2_ = TRUE;
		while (TRUE) {
			gboolean _tmp3_ = FALSE;
			guint _tmp5_ = 0U;
			guint8* _tmp6_ = NULL;
			gint _tmp6__length1 = 0;
			guint _tmp7_ = 0U;
			guint8* _tmp8_ = NULL;
			gint _tmp8__length1 = 0;
			guint _tmp9_ = 0U;
			guint8 _tmp10_ = 0U;
			guint8* _tmp11_ = NULL;
			gint _tmp11__length1 = 0;
			guint _tmp12_ = 0U;
			guint8 _tmp13_ = 0U;
			_tmp3_ = _tmp2_;
			if (!_tmp3_) {
				guint _tmp4_ = 0U;
				_tmp4_ = i;
				i = _tmp4_ + 1;
			}
			_tmp2_ = FALSE;
			_tmp5_ = i;
			_tmp6_ = d1;
			_tmp6__length1 = d1_length1;
			if (!(_tmp5_ < ((guint) _tmp6__length1))) {
				break;
			}
			_tmp7_ = d;
			_tmp8_ = d1;
			_tmp8__length1 = d1_length1;
			_tmp9_ = i;
			_tmp10_ = _tmp8_[_tmp9_];
			_tmp11_ = d2;
			_tmp11__length1 = d2_length1;
			_tmp12_ = i;
			_tmp13_ = _tmp11_[_tmp12_];
			d = _tmp7_ + ((guint) (((gint) (_tmp10_ ^ _tmp13_)) > 0));
		}
	}
	result = d;
	return result;
}
