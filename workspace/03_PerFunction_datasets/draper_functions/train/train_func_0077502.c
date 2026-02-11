test_integer_component (void) {
	{
		gint ai = 0;
		ai = -100;
		{
			gboolean _tmp0_ = FALSE;
			_tmp0_ = TRUE;
			while (TRUE) {
				gint _tmp2_ = 0;
				gdouble a = 0.0;
				gint _tmp3_ = 0;
				Number* z = NULL;
				gdouble _tmp4_ = 0.0;
				Number* _tmp5_ = NULL;
				Number* _tmp6_ = NULL;
				Number* _tmp7_ = NULL;
				Number* _tmp8_ = NULL;
				gdouble expected = 0.0;
				gdouble _tmp9_ = 0.0;
				gdouble _tmp10_ = 0.0;
				Number* _tmp11_ = NULL;
				gdouble _tmp12_ = 0.0;
				gboolean _tmp13_ = FALSE;
				if (!_tmp0_) {
					gint _tmp1_ = 0;
					_tmp1_ = ai;
					ai = _tmp1_ + 1;
				}
				_tmp0_ = FALSE;
				_tmp2_ = ai;
				if (!(_tmp2_ <= 100)) {
					break;
				}
				_tmp3_ = ai;
				a = _tmp3_ / 10.0;
				_tmp4_ = a;
				_tmp5_ = number_new_double (_tmp4_);
				_tmp6_ = _tmp5_;
				_tmp7_ = number_integer_component (_tmp6_);
				_tmp8_ = _tmp7_;
				_number_unref0 (_tmp6_);
				z = _tmp8_;
				_tmp9_ = a;
				_tmp10_ = trunc (_tmp9_);
				expected = _tmp10_;
				_tmp11_ = z;
				_tmp12_ = expected;
				_tmp13_ = double_matches (_tmp11_, _tmp12_);
				if (!_tmp13_) {
					gdouble _tmp14_ = 0.0;
					Number* _tmp15_ = NULL;
					gdouble _tmp16_ = 0.0;
					gdouble _tmp17_ = 0.0;
					gchar* _tmp18_ = NULL;
					gchar* _tmp19_ = NULL;
					_tmp14_ = a;
					_tmp15_ = z;
					_tmp16_ = number_to_double (_tmp15_);
					_tmp17_ = expected;
					_tmp18_ = g_strdup_printf ("(%f).integer_component () -> %f, expected %f", _tmp14_, _tmp16_, _tmp17_);
					_tmp19_ = _tmp18_;
					fail (_tmp19_);
					_g_free0 (_tmp19_);
					_number_unref0 (z);
					return;
				}
				_number_unref0 (z);
			}
		}
	}
	pass (NULL);
}
