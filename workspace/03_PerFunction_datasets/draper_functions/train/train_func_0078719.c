checkMaybeCnkPat(l,p)
Int  l;
Cell p; {
#if NPLUSK
    Cell h = getHead(p);

    if (argCount==2 && isVar(h) && textOf(h)==textPlus) {
	Cell v = arg(fun(p));
	if (!isVar(v)) {
	    ERRMSG(l) "First argument in (n+k) pattern must be a variable"
	    EEND;
	}
	if (!isInt(arg(p))) {
	    ERRMSG(l) "Second argument in (n+k) pattern must be an integer"
	    EEND;
	}
	if (intOf(arg(p))<=0) {
	    ERRMSG(l) "Integer k in (n+k) pattern must be > 0"
	    EEND;
	}
	fst(fun(p))	 = ADDPAT;
	intValOf(fun(p)) = intOf(arg(p));
	arg(p)		 = checkPat(l,v);
	return p;
    }
#endif
    return checkApPat(l,0,p);
}
