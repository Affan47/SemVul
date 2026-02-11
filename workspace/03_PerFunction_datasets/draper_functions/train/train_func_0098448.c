Cudd_addThreshold(
  DdManager * dd,
  DdNode ** f,
  DdNode ** g)
{
    DdNode *F, *G;

    F = *f; G = *g;
    if (F == G || F == DD_PLUS_INFINITY(dd)) return(F);
    if (cuddIsConstant(F) && cuddIsConstant(G)) {
	if (cuddV(F) >= cuddV(G)) {
	    return(F);
	} else {
	    return(DD_ZERO(dd));
	}
    }
    return(NULL);

}
