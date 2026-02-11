new_dlink(Dlist *l,const void *data,const char *fname)
{
    DlistElement *result;

    if (l->Heap == NULL) {
    	result = l->Allocator->malloc(sizeof(*result)+l->ElementSize);
    }
    else result = iHeap.NewObject(l->Heap);
    if (result == NULL) {
    	l->RaiseError(fname,CONTAINER_ERROR_NOMEMORY);
    }
    else {
    	result->Next = NULL;
    	result->Previous = NULL;
    	memcpy(&result->Data,data,l->ElementSize);
    }
    return result;
}
