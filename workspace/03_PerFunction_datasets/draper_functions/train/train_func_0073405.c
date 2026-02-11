control_points_adjacent (double xval)
{
	Glib::Threads::Mutex::Lock lm (_lock);
	iterator i;
	ControlEvent cp (xval, 0.0f);
	std::pair<iterator,iterator> ret;

	ret.first = _events.end();
	ret.second = _events.end();

	for (i = lower_bound (_events.begin(), _events.end(), &cp, time_comparator); i != _events.end(); ++i) {

		if (ret.first == _events.end()) {
			if ((*i)->when >= xval) {
				if (i != _events.begin()) {
					ret.first = i;
					--ret.first;
				} else {
					return ret;
				}
			}
		}

		if ((*i)->when > xval) {
			ret.second = i;
			break;
		}
	}

	return ret;
}
