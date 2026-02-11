MakePrime(
  const BDD& F) const
{
    DdManager *mgr = checkSameManager(F);
    if (!Cudd_CheckCube(mgr, node)) {
        p->errorHandler("Invalid argument.");
    }
    DdNode *result = Cudd_bddMakePrime(mgr, node, F.node);
    checkReturnValue(result);
    return BDD(p, result);

}
