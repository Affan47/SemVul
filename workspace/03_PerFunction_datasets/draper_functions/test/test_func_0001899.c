__lambda9_ (CandidatePanel* self, CandidateArea* w, guint i, guint b, guint s) {
	guint _tmp0_ = 0U;
	guint _tmp1_ = 0U;
	guint _tmp2_ = 0U;
	g_return_if_fail (w != NULL);
	_tmp0_ = i;
	_tmp1_ = b;
	_tmp2_ = s;
	g_signal_emit_by_name (self, "candidate-clicked", _tmp0_, _tmp1_, _tmp2_);
}
