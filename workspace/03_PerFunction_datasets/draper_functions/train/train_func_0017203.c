rt_safe_earliest_event_discrete_unlocked (double start, double& x, double& y, bool inclusive) const
{
	build_search_cache_if_necessary (start);

	if (_search_cache.first != _events.end()) {
		const ControlEvent* const first = *_search_cache.first;

		const bool past_start = (inclusive ? first->when >= start : first->when > start);


		if (past_start) {

			x = first->when;
			y = first->value;


			_search_cache.left = x;
			++_search_cache.first;

			assert(x >= start);
			return true;

		} else {
			return false;
		}


	} else {
		return false;
	}
}
