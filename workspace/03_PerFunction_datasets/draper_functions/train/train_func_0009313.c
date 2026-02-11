depCompType(l,tvs,t)
Int  l;
List tvs;
Type t; {
    Int  ntvs = length(tvs);
    List nfr  = NIL;
    if (isPolyType(t)) {
	List vs = fst(snd(t));
	t	= monotypeOf(t);
	tvs	= checkQuantVars(l,vs,tvs,t);
	nfr	= replicate(length(vs),NIL);
    }

    if (isQualType(t)) {
	map2Over(depPredExp,l,tvs,fst(snd(t)));
	snd(snd(t)) = depTypeExp(l,tvs,snd(snd(t)));


    } else {
	t = depTypeExp(l,tvs,t);
    }

    if (isNull(nfr)) {
	return t;
    }

    take(ntvs,tvs);
    return mkPolyType(nfr,t);
}
