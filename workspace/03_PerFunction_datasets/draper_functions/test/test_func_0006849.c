run_task(Task *)
{
    bool worked = false;

  retry:

    if (!_p && (_p = input(0).pull())) {
	if (!_p->timestamp_anno().sec())
	    _p->timestamp_anno().assign_now();
	_p->timestamp_anno() += _delay;
    }

    if (_p) {
	Timestamp now = Timestamp::now();
	if (_p->timestamp_anno() <= now) {

	    output(0).push(_p);
	    _p = 0;
	    worked = true;
	    goto retry;
	}

	Timestamp expiry = _p->timestamp_anno() - Timer::adjustment();
	if (expiry <= now)

	    ;
	else {

	    _timer.schedule_at(expiry);
	    return false;
	}
    } else {

	if (!_signal)
	    return false;
    }

    _task.fast_reschedule();
    return worked;
}
