ddBddToAddRecur(
  DdManager * dd,
  DdNode * B)
{
    DdNode *one;
    DdNode *res, *res1, *T, *E, *Bt, *Be;
    int complement = 0;

    statLine(dd);
    one = DD_ONE(dd);

    if (Cudd_IsConstant(B)) {
	if (B == one) {
	    res = one;
	} else {
	    res = DD_ZERO(dd);
	}
	return(res);
    }

    res = cuddCacheLookup1(dd,ddBddToAddRecur,B);
    if (res != NULL) return(res);

    if (Cudd_IsComplement(B)) {
	complement = 1;
	Bt = cuddT(Cudd_Regular(B));
	Be = cuddE(Cudd_Regular(B));
    } else {
	Bt = cuddT(B);
	Be = cuddE(B);
    }

    T = ddBddToAddRecur(dd, Bt);
    if (T == NULL) return(NULL);
    cuddRef(T);

    E = ddBddToAddRecur(dd, Be);
    if (E == NULL) {
	Cudd_RecursiveDeref(dd, T);
	return(NULL);
    }
    cuddRef(E);


    res = cuddUniqueInter(dd, (int) Cudd_Regular(B)->index, T, E);
    if (res == NULL) {
	Cudd_RecursiveDeref(dd ,T);
	Cudd_RecursiveDeref(dd ,E);
	return(NULL);
    }
    cuddDeref(T);
    cuddDeref(E);

    if (complement) {
	cuddRef(res);
	res1 = cuddAddCmplRecur(dd, res);
	if (res1 == NULL) {
	    Cudd_RecursiveDeref(dd, res);
	    return(NULL);
	}
	cuddRef(res1);
	Cudd_RecursiveDeref(dd, res);
	res = res1;
	cuddDeref(res);
    }


    cuddCacheInsert1(dd,ddBddToAddRecur,B,res);

    return(res);

}
