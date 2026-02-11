pull(int)
{

    Client *stridden = _list->_next;
    Client *c = stridden;
    Packet *p = 0;
    while (c != _list && !p) {
	if (c->_signal)
	    p = input(c->_port).pull();
	c->stride();
	c = c->_next;
    }


    _list->_next = c;
    c->_prev = _list;


    while (stridden != c) {
	Client *next = stridden->_next;
	_list->insert(stridden);

	stridden = next;
    }

    return p;
}
