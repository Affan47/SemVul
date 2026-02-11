SupportIndices(const vector<ABDD>& roots) const
{
    unsigned int *support;
    int n = roots.size();
    DdManager *mgr = p->manager;
    DdNode **F = new DdNode *[n];
    for (int i = 0; i < n; i++) {
	F[i] = roots[i].getNode();
    }
    int size = Cudd_VectorSupportIndices(mgr, F, n, (int **)&support);
    delete [] F;
    checkReturnValue(size >= 0);

    vector<unsigned int> indices(support, support+size);
    if (support) free(support);
    return indices;

}
