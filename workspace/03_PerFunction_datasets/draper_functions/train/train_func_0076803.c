SupportIndices() const
{
    unsigned int *support;
    DdManager *mgr = p->manager;
    int size = Cudd_SupportIndices(mgr, node, (int **)&support);
    checkReturnValue(size >= 0);

    vector<unsigned int> indices(support, support+size);
    if (support) free(support);
    return indices;

}
