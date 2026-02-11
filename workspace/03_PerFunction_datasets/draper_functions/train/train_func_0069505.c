skk_simple_candidate_list_real_cursor_up (SkkCandidateList* base) {
	SkkSimpleCandidateList * self;
	gboolean result = FALSE;
	gint _tmp0_;
	gint _tmp1_;
	self = (SkkSimpleCandidateList*) base;
	_tmp0_ = self->priv->_cursor_pos;
	g_assert (_tmp0_ >= 0);
	_tmp1_ = self->priv->_cursor_pos;
	if (_tmp1_ > 0) {
		gint _tmp2_;
		_tmp2_ = self->priv->_cursor_pos;
		self->priv->_cursor_pos = _tmp2_ - 1;
		g_object_notify ((GObject*) self, "cursor-pos");
		result = TRUE;
		return result;
	}
	result = FALSE;
	return result;
}
