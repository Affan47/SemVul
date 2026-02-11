fso_framework_bin_builder_append_align (FsoFrameworkBinBuilder* self) {
	guint _tmp0_ = 0U;
	guint align_bytes = 0U;
	guint _tmp1_ = 0U;
	GList* _tmp2_ = NULL;
	guint _tmp3_ = 0U;
	guint _tmp4_ = 0U;
	guint _tmp5_ = 0U;
	guint _tmp6_ = 0U;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->_alignment;
	if (_tmp0_ == ((guint) 0)) {
		return;
	}
	_tmp1_ = self->priv->_alignment;
	_tmp2_ = self->_data;
	_tmp3_ = g_list_length (_tmp2_);
	_tmp4_ = self->priv->_alignment;
	align_bytes = _tmp1_ - (_tmp3_ % _tmp4_);
	_tmp5_ = align_bytes;
	_tmp6_ = self->priv->_alignment;
	if (_tmp5_ != _tmp6_) {
		{
			gint i = 0;
			i = 0;
			{
				gboolean _tmp7_ = FALSE;
				_tmp7_ = TRUE;
				while (TRUE) {
					gboolean _tmp8_ = FALSE;
					gint _tmp10_ = 0;
					guint _tmp11_ = 0U;
					guint8 _tmp12_ = 0U;
					_tmp8_ = _tmp7_;
					if (!_tmp8_) {
						gint _tmp9_ = 0;
						_tmp9_ = i;
						i = _tmp9_ + 1;
					}
					_tmp7_ = FALSE;
					_tmp10_ = i;
					_tmp11_ = align_bytes;
					if (!(((guint) _tmp10_) < _tmp11_)) {
						break;
					}
					_tmp12_ = self->priv->_alignment_byte;
					self->_data = g_list_append (self->_data, (gpointer) ((guintptr) _tmp12_));
				}
			}
		}
	}
}
