skk_context_filter_forwarded_cb (SkkContext* self, SkkKeyEvent* key) {
	SkkKeyEvent* _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (key != NULL);
	_tmp0_ = key;
	skk_context_process_key_event_internal (self, _tmp0_);
}
