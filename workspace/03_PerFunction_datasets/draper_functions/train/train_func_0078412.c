Cudd_VectorSupport(
  DdManager * dd ,
  DdNode ** F ,
  int  n )
{
    int	*support;
    DdNode *res;
    int	j;
    int size = Cudd_VectorSupportIndices(dd, F, n, &support);
    if (size == CUDD_OUT_OF_MEM)
        return(NULL);


    res = DD_ONE(dd);
    cuddRef(res);

    for (j = size - 1; j >= 0; j--) {
        int index = support[j];
        DdNode *var = dd->vars[index];
        DdNode *tmp = Cudd_bddAnd(dd,res,var);
        if (tmp == NULL) {
            Cudd_RecursiveDeref(dd,res);
            FREE(support);
            return(NULL);
        }
        cuddRef(tmp);
        Cudd_RecursiveDeref(dd,res);
        res = tmp;
    }

    FREE(support);
    cuddDeref(res);
    return(res);

}
