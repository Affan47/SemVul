intsIntersect(as,bs)
List as, bs; {
    List ts = NIL;
    while (nonNull(as))
	if (intIsMember(intOf(hd(as)),bs)) {
	    List temp = tl(as);
	    tl(as)    = ts;
	    ts	      = as;
	    as	      = temp;
	}
	else
	    as = tl(as);
    return ts;
}
