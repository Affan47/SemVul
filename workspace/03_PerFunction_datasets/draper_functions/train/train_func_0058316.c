initialize(ErrorHandler *errh)
{

    _queues.clear();
    _queue1 = 0;

    if (!_queue_elements.size()) {
	ElementCastTracker filter(router(),"Storage");
	int ok;
	if (output_is_push(0))
	    ok = router()->visit_downstream(this, 0, &filter);
	else
	    ok = router()->visit_upstream(this, 0, &filter);
	if (ok < 0)
	    return errh->error("flow-based router context failure");
	_queue_elements = filter.elements();
    }

    if (_queue_elements.size() == 0)
	return errh->error("no nearby Queues");
    for (int i = 0; i < _queue_elements.size(); i++)
	if (Storage *s = (Storage *)_queue_elements[i]->cast("Storage"))
	    _queues.push_back(s);
	else
	    errh->error("%<%s%> is not a Storage element", _queue_elements[i]->name().c_str());
    if (_queues.size() != _queue_elements.size())
	return -1;
    else if (_queues.size() == 1)
	_queue1 = _queues[0];

    _size.clear();
    _drops = 0;
    _count = -1;
    _last_jiffies = 0;
    return 0;
}
