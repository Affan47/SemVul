visit(Element* e, bool isoutput, int port,
			     Element *, int, int)
{
    if (Notifier* n = (Notifier*) (e->port_cast(isoutput, port, _name))) {
	if (find(_notifiers.begin(), _notifiers.end(), n) == _notifiers.end())
	    _notifiers.push_back(n);
	if (!n->signal().initialized())
	    n->initialize(_name, e->router());
	_signal += n->signal();
	Notifier::SearchOp search_op = n->search_op();
	if (search_op == Notifier::SEARCH_CONTINUE_WAKE && !_pass2) {
	    _need_pass2 = true;
	    return false;
	} else
	    return search_op != Notifier::SEARCH_STOP;

    } else if (port >= 0) {
	Bitvector flow;
	if (e->port_active(isoutput, port)) {

	    _signal = NotifierSignal::busy_signal();
	    return false;
	} else if ((e->port_flow(isoutput, port, &flow), flow.zero())
		   && e->flag_value('S') != 0) {

	    _signal = NotifierSignal::busy_signal();
	    return false;
	} else
	    return true;

    } else
	return true;
}
