cuddZddDiff(
  DdManager * zdd,
  DdNode * P,
  DdNode * Q)
{
    int		p_top, q_top;
    DdNode	*empty = DD_ZERO(zdd), *t, *e, *res;
    DdManager	*table = zdd;

    statLine(zdd);
    if (P == empty)
	return(empty);
    if (Q == empty)
	return(P);
    if (P == Q)
	return(empty);


    res = cuddCacheLookup2Zdd(table, cuddZddDiff, P, Q);
    if (res != NULL && res != DD_NON_CONSTANT)
	return(res);

    if (cuddIsConstant(P))
	p_top = P->index;
    else
	p_top = zdd->permZ[P->index];
    if (cuddIsConstant(Q))
	q_top = Q->index;
    else
	q_top = zdd->permZ[Q->index];
    if (p_top < q_top) {
	e = cuddZddDiff(zdd, cuddE(P), Q);
	if (e == NULL) return(NULL);
	cuddRef(e);
	res = cuddZddGetNode(zdd, P->index, cuddT(P), e);
	if (res == NULL) {
	    Cudd_RecursiveDerefZdd(table, e);
	    return(NULL);
	}
	cuddDeref(e);
    } else if (p_top > q_top) {
	res = cuddZddDiff(zdd, P, cuddE(Q));
	if (res == NULL) return(NULL);
    } else {
	t = cuddZddDiff(zdd, cuddT(P), cuddT(Q));
	if (t == NULL) return(NULL);
	cuddRef(t);
	e = cuddZddDiff(zdd, cuddE(P), cuddE(Q));
	if (e == NULL) {
	    Cudd_RecursiveDerefZdd(table, t);
	    return(NULL);
	}
	cuddRef(e);
	res = cuddZddGetNode(zdd, P->index, t, e);
	if (res == NULL) {
	    Cudd_RecursiveDerefZdd(table, t);
	    Cudd_RecursiveDerefZdd(table, e);
	    return(NULL);
	}
	cuddDeref(t);
	cuddDeref(e);
    }

    cuddCacheInsert2(table, cuddZddDiff, P, Q, res);

    return(res);

}
