test_or (void) {
	{
		gint a;
		a = 0;
		{
			gboolean _tmp0_;
			_tmp0_ = TRUE;
			while (TRUE) {
				gboolean _tmp1_;
				gint _tmp3_;
				_tmp1_ = _tmp0_;
				if (!_tmp1_) {
					gint _tmp2_;
					_tmp2_ = a;
					a = _tmp2_ + 1;
				}
				_tmp0_ = FALSE;
				_tmp3_ = a;
				if (!(_tmp3_ < 10)) {
					break;
				}
				{
					gint b;
					b = 0;
					{
						gboolean _tmp4_;
						_tmp4_ = TRUE;
						while (TRUE) {
							gboolean _tmp5_;
							gint _tmp7_;
							gint _tmp8_;
							Number* _tmp9_;
							Number* _tmp10_;
							gint _tmp11_;
							Number* _tmp12_;
							Number* _tmp13_;
							Number* _tmp14_ = NULL;
							Number* _tmp15_;
							Number* z;
							gint _tmp16_;
							gint _tmp17_;
							gint expected;
							Number* _tmp18_;
							gint64 _tmp19_ = 0LL;
							gint _tmp20_;
							_tmp5_ = _tmp4_;
							if (!_tmp5_) {
								gint _tmp6_;
								_tmp6_ = b;
								b = _tmp6_ + 1;
							}
							_tmp4_ = FALSE;
							_tmp7_ = b;
							if (!(_tmp7_ < 10)) {
								break;
							}
							_tmp8_ = a;
							_tmp9_ = number_new_integer ((gint64) _tmp8_);
							_tmp10_ = _tmp9_;
							_tmp11_ = b;
							_tmp12_ = number_new_integer ((gint64) _tmp11_);
							_tmp13_ = _tmp12_;
							_tmp14_ = number_or (_tmp10_, _tmp13_);
							_tmp15_ = _tmp14_;
							_number_unref0 (_tmp13_);
							_number_unref0 (_tmp10_);
							z = _tmp15_;
							_tmp16_ = a;
							_tmp17_ = b;
							expected = _tmp16_ | _tmp17_;
							_tmp18_ = z;
							_tmp19_ = number_to_integer (_tmp18_);
							_tmp20_ = expected;
							if (_tmp19_ != ((gint64) _tmp20_)) {
								gint _tmp21_;
								gint _tmp22_;
								Number* _tmp23_;
								gint64 _tmp24_ = 0LL;
								gint _tmp25_;
								gchar* _tmp26_ = NULL;
								gchar* _tmp27_;
								_tmp21_ = a;
								_tmp22_ = b;
								_tmp23_ = z;
								_tmp24_ = number_to_integer (_tmp23_);
								_tmp25_ = expected;
								_tmp26_ = g_strdup_printf ("(%d).or (%d) -> %lli, expected %d", _tmp21_, _tmp22_, _tmp24_, _tmp25_);
								_tmp27_ = _tmp26_;
								fail (_tmp27_);
								_g_free0 (_tmp27_);
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
