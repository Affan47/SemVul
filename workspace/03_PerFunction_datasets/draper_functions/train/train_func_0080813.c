skk_simple_candidate_list_real_get (SkkCandidateList* base, gint index) {
	SkkSimpleCandidateList * self;
	SkkCandidate* result = NULL;
	gint _tmp0_;
	gboolean _tmp2_ = FALSE;
	gint _tmp3_;
	gboolean _tmp7_;
	GeeArrayList* _tmp8_;
	gint _tmp9_;
	gpointer _tmp10_ = NULL;
	self = (SkkSimpleCandidateList*) base;
	_tmp0_ = index;
	if (_tmp0_ < 0) {
		gint _tmp1_;
		_tmp1_ = self->priv->_cursor_pos;
		index = _tmp1_;
	}
	_tmp3_ = index;
	if (0 <= _tmp3_) {
		gint _tmp4_;
		gint _tmp5_;
		gint _tmp6_;
		_tmp4_ = index;
		_tmp5_ = skk_candidate_list_get_size ((SkkCandidateList*) self);
		_tmp6_ = _tmp5_;
		_tmp2_ = _tmp4_ < _tmp6_;
	} else {
		_tmp2_ = FALSE;
	}
	_tmp7_ = _tmp2_;
	g_assert (_tmp7_);
	_tmp8_ = self->priv->_candidates;
	_tmp9_ = index;
	_tmp10_ = gee_abstract_list_get ((GeeAbstractList*) _tmp8_, _tmp9_);
	result = (SkkCandidate*) _tmp10_;
	return result;
}
