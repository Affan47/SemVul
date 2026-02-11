dvb_event_has_expired (DVBEvent* self) {
	gboolean result = FALSE;
	struct tm current_utc = {0};
	time_t _tmp0_ = 0;
	struct tm _tmp1_ = {0};
	time_t current_time = 0;
	time_t _tmp2_ = 0;
	time_t end_timestamp = 0;
	time_t _tmp3_ = 0;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = time (NULL);
	g_time_gm (_tmp0_, &_tmp1_);
	current_utc = _tmp1_;
	current_utc.tm_isdst = -1;
	_tmp2_ = mktime (&current_utc);
	current_time = _tmp2_;
	_tmp3_ = dvb_event_get_end_timestamp (self);
	end_timestamp = _tmp3_;
	result = end_timestamp < current_time;
	return result;
}
