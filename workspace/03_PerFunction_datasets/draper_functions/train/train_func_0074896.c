monorestrict(bs)
List bs; {
    List savePreds = preds;
    Int  line 	   = isVar(fst(hd(bs))) ? rhsLine(snd(hd(snd(snd(hd(bs))))))
					: rhsLine(snd(snd(snd(hd(bs)))));
    hd(defnBounds) = NIL;
    hd(depends)    = NODEPENDS;

    preds = NIL;
    mapProc(restrictedBindAss,bs);
    mapProc(typeBind,bs);
    improve(line,NIL,preds);
    normPreds(line);
    elimTauts();
    preds = revOnto(preds,savePreds);


    clearMarks();
    mapProc(markAssumList,tl(defnBounds));
    mapProc(markAssumList,tl(varsBounds));
    mapProc(markPred,preds);
    markBtyvs();

    if (isNull(tl(defnBounds))) {
	normPreds(line);
	if (nonNull(preds) && resolveDefs(genvarAnyAss(hd(defnBounds)),FALSE))
	    elimTauts();

	clearMarks();
	reducePreds();
	improve(line,NIL,preds);
	if (nonNull(preds))
	    resolveDefs(NIL,FALSE);
	elimTauts();

	if (nonNull(preds)) {
	    Cell v   = isVar(fst(hd(bs))) ? fst(hd(bs)) : hd(fst(hd(bs)));
	    Cell ass = findInAssumList(textOf(v),hd(varsBounds));
	    preds    = scSimplify(preds);

	    ERRMSG(line) "Unresolved top-level overloading" ETHEN
	    ERRTEXT     "\n*** Binding             : %s", textToStr(textOf(v))
	    ETHEN
	    if (nonNull(ass)) {
		ERRTEXT "\n*** Inferred type       : " ETHEN ERRTYPE(snd(ass));
	    }
	    ERRTEXT     "\n*** Outstanding context : " ETHEN
						ERRCONTEXT(copyPreds(preds));
	    ERRTEXT     "\n"
	    EEND;
	}
    }

    map1Proc(genBind,NIL,bs);
}
