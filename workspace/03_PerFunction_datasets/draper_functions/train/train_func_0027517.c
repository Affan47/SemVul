test_subtract (void) {
	{
		gint a = 0;
		a = -10;
		{
			gboolean _tmp0_ = FALSE;
			_tmp0_ = TRUE;
			while (TRUE) {
				gint _tmp2_ = 0;
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
				{
					gint b = 0;
					b = -10;
					{
						gboolean _tmp3_ = FALSE;
						_tmp3_ = TRUE;
						while (TRUE) {
							gint _tmp5_ = 0;
							Number* z = NULL;
							gint _tmp6_ = 0;
							Number* _tmp7_ = NULL;
							Number* _tmp8_ = NULL;
							gint _tmp9_ = 0;
							Number* _tmp10_ = NULL;
							Number* _tmp11_ = NULL;
							Number* _tmp12_ = NULL;
							Number* _tmp13_ = NULL;
							gint expected = 0;
							gint _tmp14_ = 0;
							gint _tmp15_ = 0;
							Number* _tmp16_ = NULL;
							gint64 _tmp17_ = 0LL;
							gint _tmp18_ = 0;
							if (!_tmp3_) {
								gint _tmp4_ = 0;
								_tmp4_ = b;
								b = _tmp4_ + 1;
							}
							_tmp3_ = FALSE;
							_tmp5_ = b;
							if (!(_tmp5_ <= 10)) {
								break;
							}
							_tmp6_ = a;
							_tmp7_ = number_new_integer ((gint64) _tmp6_);
							_tmp8_ = _tmp7_;
							_tmp9_ = b;
							_tmp10_ = number_new_integer ((gint64) _tmp9_);
							_tmp11_ = _tmp10_;
							_tmp12_ = number_subtract (_tmp8_, _tmp11_);
							_tmp13_ = _tmp12_;
							_number_unref0 (_tmp11_);
							_number_unref0 (_tmp8_);
							z = _tmp13_;
							_tmp14_ = a;
							_tmp15_ = b;
							expected = _tmp14_ - _tmp15_;
							_tmp16_ = z;
							_tmp17_ = number_to_integer (_tmp16_);
							_tmp18_ = expected;
							if (_tmp17_ != ((gint64) _tmp18_)) {
								gint _tmp19_ = 0;
								gint _tmp20_ = 0;
								Number* _tmp21_ = NULL;
								gint64 _tmp22_ = 0LL;
								gint _tmp23_ = 0;
								gchar* _tmp24_ = NULL;
								gchar* _tmp25_ = NULL;
								_tmp19_ = a;
								_tmp20_ = b;
								_tmp21_ = z;
								_tmp22_ = number_to_integer (_tmp21_);
								_tmp23_ = expected;
								_tmp24_ = g_strdup_printf ("(%d).subtract (%d) -> %lli, expected %d", _tmp19_, _tmp20_, _tmp22_, _tmp23_);
								_tmp25_ = _tmp24_;
								fail (_tmp25_);
								_g_free0 (_tmp25_);
								_number_unref0 (z);
								return;
							}
							_number_unref0 (z);
						}
					}
				}
			}
		}
	}
	pass (NULL);
}
