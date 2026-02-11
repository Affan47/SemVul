fso_framework_bin_builder_set_uint64 (FsoFrameworkBinBuilder* self, guint64 val, gint position) {
	GList* l = NULL;
	gint _tmp0_ = 0;
	GList* _tmp1_ = NULL;
	gint i = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = position;
	_tmp1_ = fso_framework_bin_builder_get_at (self, _tmp0_, (guint) 8);
	l = _tmp1_;
	i = 0;
	{
		gboolean _tmp2_ = FALSE;
		i = 1;
		_tmp2_ = TRUE;
		while (TRUE) {
			gboolean _tmp3_ = FALSE;
			gboolean _tmp5_ = FALSE;
			gint _tmp6_ = 0;
			gboolean _tmp8_ = FALSE;
			GList* _tmp9_ = NULL;
			guint64 _tmp10_ = 0ULL;
			gint _tmp11_ = 0;
			guint8 _tmp12_ = 0U;
			GList* _tmp13_ = NULL;
			GList* _tmp14_ = NULL;
			_tmp3_ = _tmp2_;
			if (!_tmp3_) {
				gint _tmp4_ = 0;
				_tmp4_ = i;
				i = _tmp4_ + 1;
			}
			_tmp2_ = FALSE;
			_tmp6_ = i;
			if (_tmp6_ <= 8) {
				GList* _tmp7_ = NULL;
				_tmp7_ = l;
				_tmp5_ = _tmp7_ != NULL;
			} else {
				_tmp5_ = FALSE;
			}
			_tmp8_ = _tmp5_;
			if (!_tmp8_) {
				break;
			}
			_tmp9_ = l;
			_tmp10_ = val;
			_tmp11_ = i;
			_tmp12_ = fso_framework_bin_builder_nth_byte (_tmp10_, (guint) (8 - _tmp11_));
			_tmp9_->data = (gpointer) ((guintptr) _tmp12_);
			_tmp13_ = l;
			_tmp14_ = _tmp13_->next;
			l = _tmp14_;
		}
	}
}
