live_reconfigure(Vector<String> &conf, ErrorHandler *errh)
{

    Storage::index_type old_capacity = _capacity;

    if (SimpleQueue::configure(conf, errh) < 0)
	return -1;
    if (_capacity == old_capacity || !_q)
	return 0;
    Storage::index_type new_capacity = _capacity;
    _capacity = old_capacity;

    Packet **new_q = (Packet **) CLICK_LALLOC(sizeof(Packet *) * (new_capacity + 1));
    if (new_q == 0)
	return errh->error("out of memory");

    Storage::index_type i, j;
    for (i = _head, j = 0; i != _tail && j != new_capacity; i = next_i(i))
	new_q[j++] = _q[i];
    for (; i != _tail; i = next_i(i))
	_q[i]->kill();

    CLICK_LFREE(_q, sizeof(Packet *) * (_capacity + 1));
    _q = new_q;
    _head = 0;
    _tail = j;
    _capacity = new_capacity;
    return 0;
}
