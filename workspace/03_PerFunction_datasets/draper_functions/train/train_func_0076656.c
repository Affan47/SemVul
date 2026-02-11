tracker_needle_result_overflow (TrackerNeedle* self) {
	gchar* str = NULL;
	const gchar* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	gchar* _tmp2_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = _ ("Search criteria was too generic");
	_tmp1_ = _ ("Only the first 500 items will be displayed");
	_tmp2_ = g_strdup_printf ("%s\n<small>%s</small>", _tmp0_, _tmp1_);
	str = _tmp2_;
	tracker_needle_show_info_message (self, str, GTK_MESSAGE_INFO);
	_g_free0 (str);
}
