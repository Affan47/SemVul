test_fractional_part (void) {
	{
		gint ai;
		ai = -100;
		{
			gboolean _tmp0_;
			_tmp0_ = TRUE;
			while (TRUE) {
				gboolean _tmp1_;
				gint _tmp3_;
				gint _tmp4_;
				gdouble a;
				gdouble _tmp5_;
				Number* _tmp6_;
				Number* _tmp7_;
				Number* _tmp8_ = NULL;
				Number* _tmp9_;
				Number* z;
				gdouble _tmp10_;
				gdouble _tmp11_;
				gdouble _tmp12_ = 0.0;
				gdouble expected;
				Number* _tmp13_;
				gdouble _tmp14_;
				gboolean _tmp15_ = FALSE;
				_tmp1_ = _tmp0_;
				if (!_tmp1_) {
					gint _tmp2_;
					_tmp2_ = ai;
					ai = _tmp2_ + 1;
				}
				_tmp0_ = FALSE;
				_tmp3_ = ai;
				if (!(_tmp3_ <= 100)) {
					break;
				}
				_tmp4_ = ai;
				a = _tmp4_ / 10.0;
				_tmp5_ = a;
				_tmp6_ = number_new_double (_tmp5_);
				_tmp7_ = _tmp6_;
				_tmp8_ = number_fractional_part (_tmp7_);
				_tmp9_ = _tmp8_;
				_number_unref0 (_tmp7_);
				z = _tmp9_;
				_tmp10_ = a;
				_tmp11_ = a;
				_tmp12_ = floor (_tmp11_);
				expected = _tmp10_ - _tmp12_;
				_tmp13_ = z;
				_tmp14_ = expected;
				_tmp15_ = double_matches (_tmp13_, _tmp14_);
				if (!_tmp15_) {
					gdouble _tmp16_;
					Number* _tmp17_;
					gdouble _tmp18_ = 0.0;
					gdouble _tmp19_;
					gchar* _tmp20_ = NULL;
					gchar* _tmp21_;
					_tmp16_ = a;
					_tmp17_ = z;
					_tmp18_ = number_to_double (_tmp17_);
					_tmp19_ = expected;
					_tmp20_ = g_strdup_printf ("(%f).fractional_part () -> %f, expected %f", _tmp16_, _tmp18_, _tmp19_);
					_tmp21_ = _tmp20_;
					fail (_tmp21_);
					_g_free0 (_tmp21_);
					_number_unref0 (z);
					return;
				}
				_number_unref0 (z);
			}
		}
	}
	pass (NULL);
}
