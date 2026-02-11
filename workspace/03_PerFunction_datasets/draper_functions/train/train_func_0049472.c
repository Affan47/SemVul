PSReadFgColor (istream& in, Graphic* gs) {
    Skip(in);
    in >> _buf;

    if (
        _buf[0] == 'c' && (_buf[1] == 'f' || _psversion < PSV_FGANDBGCOLOR)
    ) {
	char lookahead = 'u';
	boolean undefined = false;
	char name[100];
	ColorIntensity r = 0, g = 0, b = 0;

	in >> lookahead;
	in.putback(lookahead);

	if (lookahead == 'u') {
	    undefined = true;

	} else {
	    in >> name;

	    if (_psversion >= PSV_FGANDBGCOLOR) {
		in >> r >> g >> b;
	    }
	}

	if (undefined || !in.good()) {
	    gs->SetColors(nil, gs->GetBgColor());

	} else {
	    int ir = Math::round(r * float(0xffff));
	    int ig = Math::round(g * float(0xffff));
	    int ib = Math::round(b * float(0xffff));

	    PSColor* fgcolor = FindColor(name, ir, ig, ib);
	    gs->SetColors(fgcolor, gs->GetBgColor());
	}
    }
}
