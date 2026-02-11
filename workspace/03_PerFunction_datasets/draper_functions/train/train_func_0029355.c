Cudd_addRoundOff(
  DdManager * dd,
  DdNode * f,
  int  N)
{
    DdNode *res;
    double trunc = pow(10.0,(double)N);

    do {
	dd->reordered = 0;
	res = cuddAddRoundOffRecur(dd,f,trunc);
    } while (dd->reordered == 1);
    return(res);

}
