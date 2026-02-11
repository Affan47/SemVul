Cudd_addBddThreshold(
  DdManager * dd,
  DdNode * f,
  CUDD_VALUE_TYPE  value)
{
    DdNode *res;
    DdNode *val;

    val = cuddUniqueConst(dd,value);
    if (val == NULL) return(NULL);
    cuddRef(val);

    do {
	dd->reordered = 0;
	res = addBddDoThreshold(dd, f, val);
    } while (dd->reordered == 1);

    if (res == NULL) {
	Cudd_RecursiveDeref(dd, val);
	return(NULL);
    }
    cuddRef(res);
    Cudd_RecursiveDeref(dd, val);
    cuddDeref(res);
    return(res);

}
