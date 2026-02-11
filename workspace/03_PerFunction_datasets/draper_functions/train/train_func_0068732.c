contacts_revealer_animate_cb (ContactsRevealer* self) {
	gboolean result = FALSE;
	gint64 now = 0LL;
	gint64 _tmp0_ = 0LL;
	gint64 _tmp1_ = 0LL;
	gdouble _tmp2_ = 0.0;
	gdouble _tmp3_ = 0.0;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = g_get_monotonic_time ();
	now = _tmp0_;
	_tmp1_ = now;
	contacts_revealer_animate_step (self, _tmp1_);
	_tmp2_ = self->priv->current_pos;
	_tmp3_ = self->priv->target_pos;
	if (_tmp2_ == _tmp3_) {
		self->priv->timeout = (guint) 0;
		result = FALSE;
		return result;
	}
	result = TRUE;
	return result;
}
