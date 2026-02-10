Ns_IndexFindMultiple(Ns_Index *indexPtr, void *key)
{
    void **firstPtrPtr;
    void **retPtrPtr;
    int    i;
    int    n;


    firstPtrPtr = (void **) bsearch(key, indexPtr->el, (size_t)indexPtr->n,
				    sizeof(void *), indexPtr->CmpKeyWithEl);

    if (firstPtrPtr == NULL) {
        return NULL;
    } else {


        while (firstPtrPtr != indexPtr->el
            && indexPtr->CmpKeyWithEl(key, firstPtrPtr - 1) == 0) {
            firstPtrPtr--;
        }


        n = indexPtr->n - (firstPtrPtr - indexPtr->el);
        for (i = 1; i < n &&
		 indexPtr->CmpKeyWithEl(key, firstPtrPtr + i) == 0; i++)
	    ;


        retPtrPtr = ns_malloc((i + 1) * sizeof(void *));
        memcpy(retPtrPtr, firstPtrPtr, i * sizeof(void *));
        retPtrPtr[i] = NULL;

        return retPtrPtr;
    }
}
