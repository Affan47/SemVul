Cudd_addBddIthBit(
  DdManager * dd,
  DdNode * f,
  int  bit)
{
    DdNode *res;
    DdNode *index;

    index = cuddUniqueConst(dd,(CUDD_VALUE_TYPE) bit);
    if (index == NULL) return(NULL);
    cuddRef(index);

    do {
	dd->reordered = 0;
	res = addBddDoIthBit(dd, f, index);
    } while (dd->reordered == 1);

    if (res == NULL) {
	Cudd_RecursiveDeref(dd, index);
	return(NULL);
    }
    cuddRef(res);
    Cudd_RecursiveDeref(dd, index);
    cuddDeref(res);
    return(res);

}
