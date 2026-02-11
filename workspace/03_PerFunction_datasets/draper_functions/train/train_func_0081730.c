test_reciprocal (void) {
	{
		gint a;
		a = -10;
		{
			gboolean _tmp0_;
			_tmp0_ = TRUE;
			while (TRUE) {
				gboolean _tmp1_;
				gint _tmp3_;
				gint _tmp4_;
				gint _tmp5_;
				Number* _tmp6_;
				Number* _tmp7_;
				Number* _tmp8_ = NULL;
				Number* _tmp9_;
				Number* z;
				gint _tmp10_;
				gdouble expected;
				Number* _tmp11_;
				gdouble _tmp12_;
				gboolean _tmp13_ = FALSE;
				gdouble _tmp20_;
				Number* _tmp21_;
				Number* _tmp22_;
				Number* _tmp23_ = NULL;
				Number* _tmp24_;
				gint _tmp25_;
				gboolean _tmp26_ = FALSE;
				_tmp1_ = _tmp0_;
				if (!_tmp1_) {
					gint _tmp2_;
					_tmp2_ = a;
					a = _tmp2_ + 1;
				}
				_tmp0_ = FALSE;
				_tmp3_ = a;
				if (!(_tmp3_ <= 10)) {
					break;
				}
				_tmp4_ = a;
				if (_tmp4_ == 0) {
					continue;
				}
				_tmp5_ = a;
				_tmp6_ = number_new_double ((gdouble) _tmp5_);
				_tmp7_ = _tmp6_;
				_tmp8_ = number_reciprocal (_tmp7_);
				_tmp9_ = _tmp8_;
				_number_unref0 (_tmp7_);
				z = _tmp9_;
				_tmp10_ = a;
				expected = 1.0 / _tmp10_;
				_tmp11_ = z;
				_tmp12_ = expected;
				_tmp13_ = double_matches (_tmp11_, _tmp12_);
				if (!_tmp13_) {
					gint _tmp14_;
					Number* _tmp15_;
					gdouble _tmp16_ = 0.0;
					gdouble _tmp17_;
					gchar* _tmp18_ = NULL;
					gchar* _tmp19_;
					_tmp14_ = a;
					_tmp15_ = z;
					_tmp16_ = number_to_double (_tmp15_);
					_tmp17_ = expected;
					_tmp18_ = g_strdup_printf ("(%f).reciprocal () -> %f, expected %f", (gdouble) _tmp14_, _tmp16_, _tmp17_);
					_tmp19_ = _tmp18_;
					fail (_tmp19_);
					_g_free0 (_tmp19_);
					_number_unref0 (z);
					return;
				}
				_tmp20_ = expected;
				_tmp21_ = number_new_double (_tmp20_);
				_tmp22_ = _tmp21_;
				_tmp23_ = number_reciprocal (_tmp22_);
				_number_unref0 (z);
				z = _tmp23_;
				_number_unref0 (_tmp22_);
				_tmp24_ = z;
				_tmp25_ = a;
				_tmp26_ = double_matches (_tmp24_, (gdouble) _tmp25_);
				if (!_tmp26_) {
					gdouble _tmp27_;
					Number* _tmp28_;
					gdouble _tmp29_ = 0.0;
					gint _tmp30_;
					gchar* _tmp31_ = NULL;
					gchar* _tmp32_;
					_tmp27_ = expected;
					_tmp28_ = z;
					_tmp29_ = number_to_double (_tmp28_);
					_tmp30_ = a;
					_tmp31_ = g_strdup_printf ("(%f).reciprocal () -> %f, expected %f", _tmp27_, _tmp29_, (gdouble) _tmp30_);
					_tmp32_ = _tmp31_;
					fail (_tmp32_);
					_g_free0 (_tmp32_);
					_number_unref0 (z);
					return;
				}
				_number_unref0 (z);
			}
		}
	}
	pass (NULL);
}
