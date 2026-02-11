cuddZddIntersect(
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
	return(empty);
    if (P == Q)
	return(P);


    res = cuddCacheLookup2Zdd(table, cuddZddIntersect, P, Q);
    if (res != NULL)
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
	res = cuddZddIntersect(zdd, cuddE(P), Q);
	if (res == NULL) return(NULL);
    } else if (p_top > q_top) {
	res = cuddZddIntersect(zdd, P, cuddE(Q));
	if (res == NULL) return(NULL);
    } else {
	t = cuddZddIntersect(zdd, cuddT(P), cuddT(Q));
	if (t == NULL) return(NULL);
	cuddRef(t);
	e = cuddZddIntersect(zdd, cuddE(P), cuddE(Q));
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

    cuddCacheInsert2(table, cuddZddIntersect, P, Q, res);

    return(res);

}
