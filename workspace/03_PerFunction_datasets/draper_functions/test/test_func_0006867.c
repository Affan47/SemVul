reap()
{
    if (_gc_sec) {
	uint32_t timeout = _active_sec - _timeout;

	Vector<uint32_t> to_free;
	for (Map::iterator iter = _map.begin(); iter.live(); iter++) {
	    FlowInfo *finfo = &iter.value();
	    if (SEC_OLDER(finfo->last_timestamp.sec(), timeout)) {
		notify(finfo->aggregate, AggregateListener::DELETE_AGG, 0);
		to_free.push_back(iter.key().a);
		to_free.push_back(iter.key().b);
	    }
	}

	for (uint32_t *u = to_free.begin(); u < to_free.end(); u += 2)
	    _map.erase(*(const HostPair *)u);
    }
    _gc_sec = _active_sec + _gc_interval;
}
