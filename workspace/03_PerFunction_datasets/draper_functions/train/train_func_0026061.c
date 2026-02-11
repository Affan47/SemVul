fso_framework_string_handling_filterByAllowedCharacters (const gchar* input, const gchar* allowed) {
	gchar* result = NULL;
	gchar* output = NULL;
	gchar* _tmp0_ = NULL;
	g_return_val_if_fail (input != NULL, NULL);
	g_return_val_if_fail (allowed != NULL, NULL);
	_tmp0_ = g_strdup ("");
	output = _tmp0_;
	{
		gint i = 0;
		i = 0;
		{
			gboolean _tmp1_ = FALSE;
			_tmp1_ = TRUE;
			while (TRUE) {
				gboolean _tmp2_ = FALSE;
				gint _tmp4_ = 0;
				const gchar* _tmp5_ = NULL;
				gint _tmp6_ = 0;
				gint _tmp7_ = 0;
				gchar* str = NULL;
				const gchar* _tmp8_ = NULL;
				gint _tmp9_ = 0;
				gchar _tmp10_ = '\0';
				gchar* _tmp11_ = NULL;
				const gchar* _tmp12_ = NULL;
				const gchar* _tmp13_ = NULL;
				gboolean _tmp14_ = FALSE;
				_tmp2_ = _tmp1_;
				if (!_tmp2_) {
					gint _tmp3_ = 0;
					_tmp3_ = i;
					i = _tmp3_ + 1;
				}
				_tmp1_ = FALSE;
				_tmp4_ = i;
				_tmp5_ = input;
				_tmp6_ = strlen (_tmp5_);
				_tmp7_ = _tmp6_;
				if (!(_tmp4_ < _tmp7_)) {
					break;
				}
				_tmp8_ = input;
				_tmp9_ = i;
				_tmp10_ = string_get (_tmp8_, (glong) _tmp9_);
				_tmp11_ = g_strdup_printf ("%c", _tmp10_);
				str = _tmp11_;
				_tmp12_ = allowed;
				_tmp13_ = str;
				_tmp14_ = string_contains (_tmp12_, _tmp13_);
				if (_tmp14_) {
					const gchar* _tmp15_ = NULL;
					const gchar* _tmp16_ = NULL;
					gchar* _tmp17_ = NULL;
					_tmp15_ = output;
					_tmp16_ = str;
					_tmp17_ = g_strconcat (_tmp15_, _tmp16_, NULL);
					_g_free0 (output);
					output = _tmp17_;
				}
				_g_free0 (str);
			}
		}
	}
	result = output;
	return result;
}
