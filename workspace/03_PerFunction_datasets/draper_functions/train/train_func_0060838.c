PSReadBrush (istream& in, Graphic* gs) {
    Skip(in);
    in >> _buf;

    if (_buf[0] == 'b') {
	char lookahead = 'u';
	boolean undefined = false;
	boolean none = false;
	int p = 0;
	float w = 0;
	int head = false;
	int tail = false;

	in >> lookahead;
	in.putback(lookahead);
	switch (lookahead) {
	case 'u':
	    undefined = true;
	    break;
	case 'n':
	    none = true;
	    break;
	default:
	    in >> p >> w >> head >> tail;
	    break;
	}

	_head = head;
	_tail = tail;

	if (undefined || !in.good()) {
	    gs->SetBrush(nil);

	} else {
            PSBrush* brush = none ? FindNoneBrush() : FindBrush(p,w);

	    gs->SetBrush(brush);
	}
    }
}
