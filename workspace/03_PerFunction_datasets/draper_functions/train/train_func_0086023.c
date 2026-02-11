ConjunctsFree(
  DdManager * dd,
  Conjuncts * factors)
{
    Cudd_RecursiveDeref(dd, factors->g);
    Cudd_RecursiveDeref(dd, factors->h);
    FREE(factors);
    return;

}
