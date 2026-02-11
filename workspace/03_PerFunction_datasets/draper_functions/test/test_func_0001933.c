pmcLetrec(co,sc,e)
Int  co;
List sc;
Pair e; {
    List fs = NIL;
    List vs = NIL;
    List ds;

    for (ds=fst(e); nonNull(ds); ds=tl(ds)) {
	Cell v     = fst(hd(ds));
	Int  arity = length(fst(hd(snd(hd(ds)))));

	if (arity==0) {
	    vs = cons(snd(hd(ds)),vs);
	    sc = cons(pair(v,mkOffset(++co)),sc);
	}
	else {
	    fs = cons(triple(inventVar(),mkInt(arity),snd(hd(ds))),fs);
	    sc = cons(pair(v,hd(fs)),sc);
	}
    }
    vs       = rev(vs);
    fs       = rev(fs);
    fst(e)   = pair(vs,fs);
    map2Over(pmcVarDef,co,sc,vs);
    map2Proc(pmcFunDef,co,sc,fs);
    snd(e)   = pmcTerm(co,sc,snd(e));
    freeFuns = diffList(freeFuns,fs);
}
