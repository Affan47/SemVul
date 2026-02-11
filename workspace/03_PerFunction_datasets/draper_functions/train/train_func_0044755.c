pull(int)
{

    Client *stridden = _list, *c;
    Packet *p = 0;
    for (c = _list; c && !p; c = c->_next) {
	if (c->_signal)
	    p = input(c - _all).pull();
	c->stride();
    }


    if ((_list = c))
	c->_pprev = &_list;


    while (stridden != c) {
	Client *next = stridden->_next;
	stridden->insert(&_list);
	stridden = next;
    }

    return p;
}
