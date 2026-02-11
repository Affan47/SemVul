insert_before(const PortT &inserter, const PortT &h)
{
    if (!add_connection(inserter, h))
	return false;

    int i = _first_conn[h.eindex()].to;
    while (i >= 0) {
	int next = _conn[i].next_to();
	if (_conn[i].to() == h && connection_live(i)
	    && _conn[i].from() != inserter)
	    change_connection_to(i, inserter);
	i = next;
    }
    return true;
}
