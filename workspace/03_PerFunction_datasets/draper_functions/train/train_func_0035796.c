test_unsigned_integer (void) {
	{
		gint a = 0;
		a = 0;
		{
			gboolean _tmp0_ = FALSE;
			_tmp0_ = TRUE;
			while (TRUE) {
				gint _tmp2_ = 0;
				Number* z = NULL;
				gint _tmp3_ = 0;
				Number* _tmp4_ = NULL;
				Number* _tmp5_ = NULL;
				guint64 _tmp6_ = 0ULL;
				gint _tmp7_ = 0;
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
				_tmp4_ = number_new_unsigned_integer ((guint64) _tmp3_);
				z = _tmp4_;
				_tmp5_ = z;
				_tmp6_ = number_to_unsigned_integer (_tmp5_);
				_tmp7_ = a;
				if (_tmp6_ != ((guint64) _tmp7_)) {
					gint _tmp8_ = 0;
					Number* _tmp9_ = NULL;
					guint64 _tmp10_ = 0ULL;
					gint _tmp11_ = 0;
					gchar* _tmp12_ = NULL;
					gchar* _tmp13_ = NULL;
					_tmp8_ = a;
					_tmp9_ = z;
					_tmp10_ = number_to_unsigned_integer (_tmp9_);
					_tmp11_ = a;
					_tmp12_ = g_strdup_printf ("Number.unsigned_integer (%d).to_unsigned_integer () -> %i, expected %i", _tmp8_, (gint) _tmp10_, _tmp11_);
					_tmp13_ = _tmp12_;
					fail (_tmp13_);
					_g_free0 (_tmp13_);
					_number_unref0 (z);
					return;
				}
				_number_unref0 (z);
			}
		}
	}
	pass (NULL);
}
