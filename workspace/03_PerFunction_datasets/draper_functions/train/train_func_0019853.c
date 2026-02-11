draw(frame *f) {

    double a,b;
    double len;
    string dir;
    Picshiftdraw sd(cout);

    try {
	switch (side) {
	    default:
	    case left_side:
		a = 0;
		b = c->map(where,y_axis);
		dir = "right";
		len = f->wid;
		break;
	    case right_side:
		a = 1;
		b = c->map(where,y_axis);
		dir = "left";
		len = f->wid;
		break;
	    case top_side:
		a = c->map(where,x_axis);
		b = 1;
		dir = "down";
		len = f->ht;
		break;
	    case bottom_side:
		a  = c->map(where,x_axis);
		b = 0;
		dir = "up";
		len = f->ht;
		break;
	}
    }
    catch (range_error& e) {
	cerr << "failed to map grid value: " << where << ": "
	     << e.what() << endl;
	return;
    }
    if ( a < 0 || a > 1 ) return;
    else a *= f->wid;
    if ( b < 0 || b > 1 ) return;
    else b *= f->ht;
    cout << "move to Frame.Origin + (" << a << ", " << b << ")" << endl;
    cout << "line ";
    switch (desc.ld) {
	case invis:
	    cout << "invis ";
	    break;
	case solid:
	default:
	    break;
	case dotted:
	    cout << "dotted ";
	    if ( desc.param )
		cout << desc.param << " ";
	    break;
	case dashed:
	    cout << "dashed ";
	    if ( desc.param )
		cout << desc.param << " ";
	    break;
    }
    if ( !compat_mode ) {
	if ( desc.color ) cout << " color " << *desc.color << " ";
	if ( desc.thick ) cout << " thickness " << desc.thick << " ";
    }
    cout << dir << " " << len << endl;
    if ( prt ) {
	cout << "move to Frame.Origin + (" << a << ", " << b << ")" << endl;
	cout << "move " << dir << " -0.125" << endl;

	for_each(shift.begin(), shift.end(), sd);

	quote(prt);
	PicDisplayString pprt(*prt);
	pprt.draw(f);
	cout << " at Here" << endl;
    }
}
