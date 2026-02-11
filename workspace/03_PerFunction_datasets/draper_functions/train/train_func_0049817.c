gee_array_list_wrap_float (GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func, gfloat** data, int data_length1, int* result_length1) {
	gpointer* result = NULL;
	gpointer* arr = NULL;
	gfloat** _tmp0_ = NULL;
	gint _tmp0__length1 = 0;
	gpointer* _tmp1_ = NULL;
	gint arr_length1 = 0;
	gint _arr_size_ = 0;
	gpointer* _tmp14_ = NULL;
	gint _tmp14__length1 = 0;
	_tmp0_ = data;
	_tmp0__length1 = data_length1;
	_tmp1_ = g_new0 (gpointer, _tmp0__length1);
	arr = _tmp1_;
	arr_length1 = _tmp0__length1;
	_arr_size_ = arr_length1;
	{
		guint i = 0U;
		i = (guint) 0;
		{
			gboolean _tmp2_ = FALSE;
			_tmp2_ = TRUE;
			while (TRUE) {
				gboolean _tmp3_ = FALSE;
				guint _tmp5_ = 0U;
				gfloat** _tmp6_ = NULL;
				gint _tmp6__length1 = 0;
				gpointer* _tmp7_ = NULL;
				gint _tmp7__length1 = 0;
				guint _tmp8_ = 0U;
				gfloat** _tmp9_ = NULL;
				gint _tmp9__length1 = 0;
				guint _tmp10_ = 0U;
				gfloat* _tmp11_ = NULL;
				gpointer _tmp12_ = NULL;
				gpointer _tmp13_ = NULL;
				_tmp3_ = _tmp2_;
				if (!_tmp3_) {
					guint _tmp4_ = 0U;
					_tmp4_ = i;
					i = _tmp4_ + 1;
				}
				_tmp2_ = FALSE;
				_tmp5_ = i;
				_tmp6_ = data;
				_tmp6__length1 = data_length1;
				if (!(_tmp5_ < ((guint) _tmp6__length1))) {
					break;
				}
				_tmp7_ = arr;
				_tmp7__length1 = arr_length1;
				_tmp8_ = i;
				_tmp9_ = data;
				_tmp9__length1 = data_length1;
				_tmp10_ = i;
				_tmp11_ = _tmp9_[_tmp10_];
				_tmp12_ = ((_tmp11_ != NULL) && (g_dup_func != NULL)) ? g_dup_func ((gpointer) _tmp11_) : ((gpointer) _tmp11_);
				_g_destroy_func0 (_tmp7_[_tmp8_]);
				_tmp7_[_tmp8_] = _tmp12_;
				_tmp13_ = _tmp7_[_tmp8_];
			}
		}
	}
	_tmp14_ = arr;
	_tmp14__length1 = arr_length1;
	if (result_length1) {
		*result_length1 = _tmp14__length1;
	}
	result = _tmp14_;
	return result;
}
