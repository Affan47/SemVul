Insert(TreeMap *tree, const void *Data, void *ExtraArgs)
{
    struct Node *p;
    CompareInfo cInfo;

    cInfo.ExtraArgs = ExtraArgs;
    cInfo.ContainerLeft = tree;
    tree->aux = &cInfo;
    p = iHeap.NewObject(tree->Heap);
    tree->aux = NULL;
    if (p == NULL)
    	return 0;
    memcpy(p->data,Data,tree->ElementSize);
    p = insert(tree, p, ExtraArgs);
    if (p) {
    	memcpy(p->data ,Data,tree->ElementSize);
    	return 1;
    }
    return 0;

}
