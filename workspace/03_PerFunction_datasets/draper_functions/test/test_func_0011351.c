box_stroke(dbl x1, dbl y1, dbl x2, dbl y2, bool reverse) {
	if (g.inpath) {
		if (reverse) {
			out() << x1 << " " << y1 << " moveto " << x1 << " " << y2 << " l " <<
			         x2 << " " << y2 << " l " << x2 << " " << y1 << " l closepath" << endl;
		} else {
			xdbox(x1,y1,x2,y2);
		}
	} else {
		g_flush();
		out() << "newpath ";
		xdbox(x1,y1,x2,y2);
		out() << "stroke" << endl;
		ps_nvec = 0;
	}
}
