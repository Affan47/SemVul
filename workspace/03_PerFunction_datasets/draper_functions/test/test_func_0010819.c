checkQuantVars(line,vs,tvs,body)
Int  line;
List vs;
List tvs;
Cell body; {
    if (nonNull(vs)) {
	List bvs = typeVarsIn(body,NIL,NIL,NIL);
	List us  = vs;
	for (; nonNull(us); us=tl(us)) {
	    Text u = textOf(hd(us));
	    if (varIsMember(u,tl(us))) {
		ERRMSG(line) "Repeated quantified variable %s",
			     textToStr(u)
		EEND;
	    }
#if 0
	    if (varIsMember(u,tvs)) {
		ERRMSG(line) "Local quantifier for %s hides an outer use",
			     textToStr(u)
		EEND;
	    }
#endif
	    if (!varIsMember(u,bvs)) {
		ERRMSG(line) "Locally quantified variable %s is not used",
			     textToStr(u)
		EEND;
	    }
	}
	tvs = appendOnto(tvs,vs);
    }
    return tvs;
}
