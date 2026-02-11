ReadFgColor (istream& in, void* addr1, void* addr2, void* addr3, void* addr4) {
    if (!Component::use_unidraw()) return 0;

    char lookahead = '"';
    char name[BUFSIZ];
    boolean name_arg = false;
    ColorIntensity r = 0, g = 0, b = 0;
    Graphic* gs = *(Graphic**)addr1;
    char delim;
    char buf[BUFSIZ];

    ParamList::skip_space(in);
    in >> lookahead;
    in.putback(lookahead);

    if (lookahead == '"') {
        name_arg = true;
	ParamList::parse_string(in, name, BUFSIZ);
        if (!in.good()) {
	    gs->SetColors(nil, gs->GetBgColor());
	    return -1;
        }
    }

    if (name_arg) {
        in >> lookahead;
        in.putback(lookahead);
    }

    if (lookahead == ',' || !name_arg) {
        in >> delim >> r >> delim >> g >> delim >> b;
	if (!in.good()) {
	    gs->SetColors(nil, gs->GetBgColor());
	    return -1;
        }
	else {
	    int ir = Math::round(r * float(0xffff));
	    int ig = Math::round(g * float(0xffff));
	    int ib = Math::round(b * float(0xffff));
	    PSColor* fgcolor = OverlayCatalog::Instance()->FindColor(name_arg ? name : "no_name", ir, ig, ib);
	    gs->SetColors(fgcolor, gs->GetBgColor());
            return 0;
	}
    }
    return -1;
}
