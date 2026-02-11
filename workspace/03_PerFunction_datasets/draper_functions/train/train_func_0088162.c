Xeqy(
  vector<ADD> x,
  vector<ADD> y)
{
    int N = x.size();
    DdManager *mgr = p->manager;
    DdNode **X = new DdNode *[N];
    DdNode **Y = new DdNode *[N];
    for (int i = 0; i < N; i++) {
	X[i] = x[i].getNode();
	Y[i] = y[i].getNode();
    }
    DdNode *result = Cudd_addXeqy(mgr, N, X, X);
    delete [] X;
    delete [] Y;
    checkReturnValue(result);
    return ADD(p, result);

}
