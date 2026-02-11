bev_timeout_event_cb(struct bufferevent *bev, short what, void *arg)
{
	struct timeout_cb_result *res = arg;
	++res->total_calls;

	if ((what & (BEV_EVENT_READING|BEV_EVENT_TIMEOUT))
	    == (BEV_EVENT_READING|BEV_EVENT_TIMEOUT)) {
		evutil_gettimeofday(&res->read_timeout_at, NULL);
		++res->n_read_timeouts;
	}
	if ((what & (BEV_EVENT_WRITING|BEV_EVENT_TIMEOUT))
	    == (BEV_EVENT_WRITING|BEV_EVENT_TIMEOUT)) {
		evutil_gettimeofday(&res->write_timeout_at, NULL);
		++res->n_write_timeouts;
	}
}
