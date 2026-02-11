read_handler(Element *e, void *thunk)
{
    TimeRange *tr = static_cast<TimeRange *>(e);
    StringAccum sa;
    switch ((intptr_t)thunk) {
    case h_range:
	sa << tr->_first << ' ' << tr->_last;
	break;
    case h_interval:
	sa << (tr->_last - tr->_first);
	break;
    }
    return sa.take_string();
}
