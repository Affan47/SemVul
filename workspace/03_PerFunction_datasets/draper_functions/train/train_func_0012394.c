minefield_view_set_use_number_border (MinefieldView* self, gboolean use_number_border) {
	gboolean _tmp0_ = FALSE;
	gboolean _tmp1_ = FALSE;
	gboolean _tmp2_ = FALSE;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->use_number_border;
	_tmp1_ = use_number_border;
	if (_tmp0_ != _tmp1_) {
		self->priv->render_size = (guint) 0;
	}
	_tmp2_ = use_number_border;
	self->priv->use_number_border = _tmp2_;
}
