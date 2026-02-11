run_task(Task *)
{
    bool worked = false;
    if (_rate.need_update(Timestamp::now())) {
	if (Packet *p = input(0).pull()) {
	    _rate.update_with(p->length());
	    worked = true;
	    output(0).push(p);
	} else if (!_signal)
	    return false;
    }
    _task.fast_reschedule();
    return worked;
}
