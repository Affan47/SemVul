fibHeap_findMinimum(struct fib_heap* heap,void** ret){
	if(!heap->minPtr){
		return FIBHEAP_EMPTY;
	}

	*ret = &(heap->minPtr->key);
	return FIBHEAP_SUCCESS;
}
