Apply(SuffixTree *tree, int(*Applyfn)(void *,void *),void *arg)
{
    if (tree == NULL || Applyfn == NULL) {
        if (tree)
            tree->RaiseError("SuffixTree.Aply",CONTAINER_ERROR_BADARG);
        else
            iError.RaiseError("SuffixTree.Apply",CONTAINER_ERROR_BADARG);
        return CONTAINER_ERROR_BADARG;
    }
    VisitNode(tree,Applyfn,tree->root,0,arg);
    return 1;
}
