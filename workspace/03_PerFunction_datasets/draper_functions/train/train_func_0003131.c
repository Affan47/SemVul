_clear(Request& r, MethodParams& params) {
	VMemcached& self=GET_SELF(r, VMemcached);
	time_t ttl=(params.count()>0) ? params.as_int(0, "expiration must be int", r) : 0;

	self.flush(ttl);
}
