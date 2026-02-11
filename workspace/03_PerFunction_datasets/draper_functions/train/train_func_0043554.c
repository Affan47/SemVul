Clear(TreeMap *tree)
{
    Iterator *it;
    void *obj;
	if (tree->DestructorFn) {
		it = NewIterator(tree);

        if (it == NULL) {
            iError.RaiseError("iTree.Clear",CONTAINER_ERROR_NOMEMORY);
            goto continuation;
        }
		for (obj = it->GetFirst(it);
			 obj != NULL;
			 obj = it->GetNext(it)) {
			tree->DestructorFn(obj);
		}
		DeleteIterator(it);
	}
continuation:
    iHeap.Clear( tree->Heap);
    tree->count = 0;
    tree->root=0;
    tree->max_size=0;
    tree->Flags=0;
    tree->timestamp=0;
    return 1;
}
