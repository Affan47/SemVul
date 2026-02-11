addFixdecl(bs,ts,cs,ps,fixdecl)
List   bs;
List   ts;
List   cs;
List   ps;
Triple fixdecl; {
    Int  line = intOf(fst3(fixdecl));
    List ops  = snd3(fixdecl);
    Cell sy   = thd3(fixdecl);

    for (; nonNull(ops); ops=tl(ops)) {
	Cell op   = hd(ops);
	Text t    = textOf(op);
	Cell attr = getAttr(bs,op);
	if (nonNull(attr)) {
	    if (nonNull(snd(attr))) {
		dupFixity(line,t);
	    }
	    snd(attr) = sy;
	} else {
	    Name n   = NIL;
	    List ts1 = ts;
	    List cs1 = cs;
	    List ps1 = ps;
	    for (; isNull(n) && nonNull(ts1); ts1=tl(ts1)) {
		Tycon tc = hd(ts1);
		if (tycon(tc).what==DATATYPE || tycon(tc).what==NEWTYPE) {
		    n = nameIsMember(t,tycon(tc).defn);
		}
	    }
	    for (; isNull(n) && nonNull(cs1); cs1=tl(cs1)) {
		n = nameIsMember(t,cclass(hd(cs1)).members);
	    }
	    for (; isNull(n) && nonNull(ps1); ps1=tl(ps1)) {
		n = nameIsMember(t,hd(ps1));
	    }

	    if (isNull(n)) {
		missFixity(line,t);
	    } else if (name(n).syntax!=NO_SYNTAX) {
		dupFixity(line,t);
	    }
	    name(n).syntax = intOf(sy);
	}
    }
}
