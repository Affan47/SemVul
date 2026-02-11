pull(int)
{
    if (!_active)
	return 0;
    if (_limit != NO_LIMIT && _count >= _limit) {
	if (_stop)
	    router()->please_stop_driver();
	return 0;
    }

    Timestamp now = Timestamp::now();
    if (_rate.need_update(now)) {
	_rate.update();
	_count++;
	Packet *p = _packet->clone();
	p->set_timestamp_anno(now);
	return p;
    } else
	return 0;
}
