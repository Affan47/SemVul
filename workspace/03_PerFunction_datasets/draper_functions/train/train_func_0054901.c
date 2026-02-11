fso_framework_bin_builder_append_uint32 (FsoFrameworkBinBuilder* self, guint32 v) {
	guint32 _tmp0_ = 0U;
	guint32 _tmp1_ = 0U;
	g_return_if_fail (self != NULL);
	_tmp0_ = v;
	_tmp1_ = fso_framework_bin_builder_uint32_convert (self, _tmp0_);
	v = _tmp1_;
	self->_data = g_list_reverse (self->_data);
	{
		gint i = 0;
		i = 0;
		{
			gboolean _tmp2_ = FALSE;
			_tmp2_ = TRUE;
			while (TRUE) {
				gboolean _tmp3_ = FALSE;
				gint _tmp5_ = 0;
				guint32 _tmp6_ = 0U;
				gint _tmp7_ = 0;
				guint8 _tmp8_ = 0U;
				_tmp3_ = _tmp2_;
				if (!_tmp3_) {
					gint _tmp4_ = 0;
					_tmp4_ = i;
					i = _tmp4_ + 1;
				}
				_tmp2_ = FALSE;
				_tmp5_ = i;
				if (!(_tmp5_ < 4)) {
					break;
				}
				_tmp6_ = v;
				_tmp7_ = i;
				_tmp8_ = fso_framework_bin_builder_nth_byte ((guint64) _tmp6_, (guint) _tmp7_);
				self->_data = g_list_prepend (self->_data, (gpointer) ((guintptr) _tmp8_));
			}
		}
	}
	self->_data = g_list_reverse (self->_data);
	fso_framework_bin_builder_append_align (self);
}
