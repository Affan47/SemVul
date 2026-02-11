cuddEstimateCofactorSimple(
  DdNode * node,
  int i)
{
    int tval, eval;

    if (Cudd_IsComplement(node->next)) {
	return(0);
    }
    node->next = Cudd_Not(node->next);
    if (cuddIsConstant(node)) {
	return(1);
    }
    tval = cuddEstimateCofactorSimple(cuddT(node),i);
    if ((int) node->index == i) return(tval);
    eval = cuddEstimateCofactorSimple(Cudd_Regular(cuddE(node)),i);
    return(1 + tval + eval);

}
