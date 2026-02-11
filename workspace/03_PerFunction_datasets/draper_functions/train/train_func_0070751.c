move_ranges (const list< RangeMove<double> >& movements)
{
	typedef list< RangeMove<double> > RangeMoveList;

	{
		Glib::Threads::Mutex::Lock lm (_lock);


		EventList old_events = _events;


		bool things_erased = false;
		for (RangeMoveList::const_iterator i = movements.begin (); i != movements.end (); ++i) {

			if (erase_range_internal (i->from, i->from + i->length, _events)) {
				things_erased = true;
			}

			if (erase_range_internal (i->to, i->to + i->length, _events)) {
				things_erased = true;
			}
		}


		if (!things_erased) {
			return false;
		}


		for (RangeMoveList::const_iterator i = movements.begin (); i != movements.end (); ++i) {
			iterator j = old_events.begin ();
			const double limit = i->from + i->length;
			const double dx    = i->to - i->from;
			while (j != old_events.end () && (*j)->when <= limit) {
				if ((*j)->when >= i->from) {
					ControlEvent* ev = new ControlEvent (**j);
					ev->when += dx;
					_events.push_back (ev);
				}
				++j;
			}
		}

		if (!_frozen) {
			_events.sort (event_time_less_than);
			unlocked_invalidate_insert_iterator ();
		} else {
			_sort_pending = true;
		}

		mark_dirty ();
	}

	maybe_signal_changed ();
	return true;
}
