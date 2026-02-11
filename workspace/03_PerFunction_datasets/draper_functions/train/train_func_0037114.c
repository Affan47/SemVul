simple_action(Packet *p)
{
    const Timestamp& tv = p->timestamp_anno();
    if (unlikely(!_ready))
	first_packet(tv);
    if (unlikely(tv < _first))
	return kill(p);
    else {
	if (!likely(tv < _last) && _last_h && _last_h_ready) {
	    VariableEnvironment scope(0);
	    scope.define(String::make_stable("t", 1), tv.unparse(), true);
	    Timestamp prev_last;
	    do {
		prev_last = _last;
		_last_h_ready = false;
		(void) _last_h->call_write(scope);
	    } while (!(tv < _last) && _last_h && _last_h_ready
		     && _last > prev_last);
	}
	if (!likely(tv < _last))
	    return kill(p);
	else
	    return p;
    }
}
