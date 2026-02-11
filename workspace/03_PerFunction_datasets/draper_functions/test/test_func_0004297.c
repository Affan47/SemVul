push(int, Packet *p)
{

    int h = _head, t = _tail, nt = next_i(t);

    if (nt != h) {
	_q[t] = p;

	_tail = nt;

	int s = size(h, nt);
	if (s > _highwater_length)
	    _highwater_length = s;

	_empty_note.wake();

    } else {
	if (_drops == 0)
	    click_chatter("%{element}: overflow", this);
	_drops++;
	p->kill();
    }
}
