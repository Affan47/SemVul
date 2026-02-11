visitSyn(path,t,syns)
List  path;
Tycon t;
List  syns; {
    if (cellIsMember(t,path)) {
	ERRMSG(tycon(t).line)
	    "Type synonyms \"%s\" and \"%s\" are mutually recursive",
	    textToStr(tycon(t).text), textToStr(tycon(hd(path)).text)
	EEND;
    } else {
	List ds    = tycon(t).kind;
	List path1 = NIL;
	for (; nonNull(ds); ds=tl(ds)) {
	    if (cellIsMember(hd(ds),syns)) {
		if (isNull(path1)) {
		    path1 = cons(t,path);
		}
		syns = visitSyn(path1,hd(ds),syns);
	    }
	}
    }
    tycon(t).defn = fullExpand(tycon(t).defn);
    return removeCell(t,syns);
}
