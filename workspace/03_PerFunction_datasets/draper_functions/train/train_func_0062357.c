VectorCompose(
  vector<BDD> vector) const
{
    DdManager *mgr = p->manager;
    int n = Cudd_ReadSize(mgr);
    DdNode **X = new DdNode *[n];
    for (int i = 0; i < n; i++) {
	X[i] = vector[i].node;
    }
    DdNode *result = Cudd_bddVectorCompose(mgr, node, X);
    delete [] X;
    checkReturnValue(result);
    return BDD(p, result);

}
