Cudd_CProjection(
  DdManager * dd,
  DdNode * R,
  DdNode * Y)
{
    DdNode *res;
    DdNode *support;

    if (Cudd_CheckCube(dd,Y) == 0) {
	(void) fprintf(dd->err,
	"Error: The third argument of Cudd_CProjection should be a cube\n");
	dd->errorCode = CUDD_INVALID_ARG;
	return(NULL);
    }


    support = Cudd_Support(dd,Y);
    if (support == NULL) return(NULL);
    cuddRef(support);

    do {
	dd->reordered = 0;
	res = cuddCProjectionRecur(dd,R,Y,support);
    } while (dd->reordered == 1);

    if (res == NULL) {
	Cudd_RecursiveDeref(dd,support);
	return(NULL);
    }
    cuddRef(res);
    Cudd_RecursiveDeref(dd,support);
    cuddDeref(res);

    return(res);

}
