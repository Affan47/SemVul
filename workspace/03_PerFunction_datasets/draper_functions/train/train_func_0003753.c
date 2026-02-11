Cudd_bddComputeCube(
  DdManager * dd,
  DdNode ** vars,
  int * phase,
  int  n)
{
    DdNode	*cube;
    DdNode	*fn;
    int         i;

    cube = DD_ONE(dd);
    cuddRef(cube);

    for (i = n - 1; i >= 0; i--) {
	if (phase == NULL || phase[i] != 0) {
	    fn = Cudd_bddAnd(dd,vars[i],cube);
	} else {
	    fn = Cudd_bddAnd(dd,Cudd_Not(vars[i]),cube);
	}
	if (fn == NULL) {
	    Cudd_RecursiveDeref(dd,cube);
	    return(NULL);
	}
	cuddRef(fn);
	Cudd_RecursiveDeref(dd,cube);
	cube = fn;
    }
    cuddDeref(cube);

    return(cube);

}
