test_invert_sign (void) {
	{
		gint a = 0;
		a = -10;
		{
			gboolean _tmp0_ = FALSE;
			_tmp0_ = TRUE;
			while (TRUE) {
				gint _tmp2_ = 0;
				Number* z = NULL;
				gint _tmp3_ = 0;
				Number* _tmp4_ = NULL;
				gint expected = 0;
				gint _tmp5_ = 0;
				Number* _tmp6_ = NULL;
				Number* _tmp7_ = NULL;
				Number* _tmp8_ = NULL;
				gint64 _tmp9_ = 0LL;
				gint _tmp10_ = 0;
				gboolean _tmp11_ = FALSE;
				if (!_tmp0_) {
					gint _tmp1_ = 0;
					_tmp1_ = a;
					a = _tmp1_ + 1;
				}
				_tmp0_ = FALSE;
				_tmp2_ = a;
				if (!(_tmp2_ <= 10)) {
					break;
				}
				_tmp3_ = a;
				_tmp4_ = number_new_integer ((gint64) _tmp3_);
				z = _tmp4_;
				_tmp5_ = a;
				expected = -_tmp5_;
				_tmp6_ = z;
				_tmp7_ = number_invert_sign (_tmp6_);
				_tmp8_ = _tmp7_;
				_tmp9_ = number_to_integer (_tmp8_);
				_tmp10_ = expected;
				_tmp11_ = _tmp9_ != ((gint64) _tmp10_);
				_number_unref0 (_tmp8_);
				if (_tmp11_) {
					gint _tmp12_ = 0;
					Number* _tmp13_ = NULL;
					Number* _tmp14_ = NULL;
					Number* _tmp15_ = NULL;
					gint64 _tmp16_ = 0LL;
					gint _tmp17_ = 0;
					gchar* _tmp18_ = NULL;
					gchar* _tmp19_ = NULL;
					_tmp12_ = a;
					_tmp13_ = z;
					_tmp14_ = number_invert_sign (_tmp13_);
					_tmp15_ = _tmp14_;
					_tmp16_ = number_to_integer (_tmp15_);
					_tmp17_ = expected;
					_tmp18_ = g_strdup_printf ("(%d).invert_sign () -> %d, expected %d", _tmp12_, (gint) _tmp16_, _tmp17_);
					_tmp19_ = _tmp18_;
					fail (_tmp19_);
					_g_free0 (_tmp19_);
					_number_unref0 (_tmp15_);
					_number_unref0 (z);
					return;
				}
				_number_unref0 (z);
			}
		}
	}
	pass (NULL);
}
