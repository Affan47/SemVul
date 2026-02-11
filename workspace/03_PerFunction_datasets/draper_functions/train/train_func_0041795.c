leaveSkolVars(l,t,o,m)
Int  l;
Type t;
Int  o;
Int  m; {
    if (nonNull(hd(localEvs))) {
	List sks = hd(skolVars);
	List sps = NIL;
	if (isNull(sks)) {
	    internal("leaveSkolVars");
	}
	markAllVars();
	do {
	    tyvar(intOf(fst(hd(sks))))->offs = UNUSED_GENERIC;
	    sks = tl(sks);
	} while (nonNull(sks));
	normPreds(l);
	sps   = elimPredsUsing(hd(localEvs),sps);
	preds = revOnto(preds,sps);
    }

    if (nonNull(hd(skolVars))) {
	List vs;
	Int  i = 0;

	clearMarks();
	for (; i<m; i++)
	    markTyvar(o+i);
	markType(t,o);

	for (vs=hd(skolVars); nonNull(vs); vs=tl(vs)) {
	    Int vn = intOf(fst(hd(vs)));
	    if (tyvar(vn)->offs == FIXED_TYVAR) {
		Cell tv = copyTyvar(vn);
		Type ty = liftRank2(t,o,m);
		ERRMSG(l) "Existentially quantified variable in inferred type"
		ETHEN
		ERRTEXT   "\n*** Variable     : " ETHEN ERRTYPE(tv);
		ERRTEXT   "\n*** From pattern : " ETHEN ERREXPR(snd(hd(vs)));
		ERRTEXT   "\n*** Result type  : " ETHEN ERRTYPE(ty);
		ERRTEXT   "\n"
		EEND;
	    }
	}

	markBtyvs();
	mapProc(markAssumList,defnBounds);
	mapProc(markAssumList,varsBounds);
	mapProc(markPred,preds);

	for (vs=hd(skolVars); nonNull(vs); vs=tl(vs)) {
	    Int vn = intOf(fst(hd(vs)));
	    if (tyvar(vn)->offs == FIXED_TYVAR) {
		ERRMSG(l)
		  "Existentially quantified variable escapes from pattern "
		ETHEN ERREXPR(snd(hd(vs)));
		ERRTEXT "\n"
		EEND;
	    }
	}
    }
    localEvs = tl(localEvs);
    skolVars = tl(skolVars);
    preds    = revOnto(preds,hd(savedPs));
    savedPs  = tl(savedPs);
}
