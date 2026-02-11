diodon_file_clipboard_item_join (const gchar* separator, gchar** array, int array_length1) {
	gchar* result = NULL;
	gchar* _result_ = NULL;
	gchar* _tmp0_ = NULL;
	gchar** _tmp1_ = NULL;
	gint _tmp1__length1 = 0;
	_tmp0_ = g_strdup ("");
	_result_ = _tmp0_;
	_tmp1_ = array;
	_tmp1__length1 = array_length1;
	if (_tmp1__length1 > 0) {
		gchar** _tmp2_ = NULL;
		gint _tmp2__length1 = 0;
		const gchar* _tmp3_ = NULL;
		gchar* _tmp4_ = NULL;
		_tmp2_ = array;
		_tmp2__length1 = array_length1;
		_tmp3_ = _tmp2_[0];
		_tmp4_ = g_strdup (_tmp3_);
		_g_free0 (_result_);
		_result_ = _tmp4_;
		{
			gint i = 0;
			i = 1;
			{
				gboolean _tmp5_ = FALSE;
				_tmp5_ = TRUE;
				while (TRUE) {
					gboolean _tmp6_ = FALSE;
					gint _tmp8_ = 0;
					gchar** _tmp9_ = NULL;
					gint _tmp9__length1 = 0;
					const gchar* _tmp10_ = NULL;
					const gchar* _tmp11_ = NULL;
					gchar* _tmp12_ = NULL;
					const gchar* _tmp13_ = NULL;
					gchar** _tmp14_ = NULL;
					gint _tmp14__length1 = 0;
					gint _tmp15_ = 0;
					const gchar* _tmp16_ = NULL;
					gchar* _tmp17_ = NULL;
					_tmp6_ = _tmp5_;
					if (!_tmp6_) {
						gint _tmp7_ = 0;
						_tmp7_ = i;
						i = _tmp7_ + 1;
					}
					_tmp5_ = FALSE;
					_tmp8_ = i;
					_tmp9_ = array;
					_tmp9__length1 = array_length1;
					if (!(_tmp8_ < _tmp9__length1)) {
						break;
					}
					_tmp10_ = _result_;
					_tmp11_ = separator;
					_tmp12_ = g_strconcat (_tmp10_, _tmp11_, NULL);
					_g_free0 (_result_);
					_result_ = _tmp12_;
					_tmp13_ = _result_;
					_tmp14_ = array;
					_tmp14__length1 = array_length1;
					_tmp15_ = i;
					_tmp16_ = _tmp14_[_tmp15_];
					_tmp17_ = g_strconcat (_tmp13_, _tmp16_, NULL);
					_g_free0 (_result_);
					_result_ = _tmp17_;
				}
			}
		}
	}
	result = _result_;
	return result;
}
