Ntr_InitHeap(
  int size)
{
    NtrHeap *heap;

    heap = ALLOC(NtrHeap,1);
    if (heap == NULL) return(NULL);
    heap->size = size;
    heap->nslots = 0;
    heap->slots = ALLOC(NtrHeapSlot,size);
    if (heap->slots == NULL) {
	FREE(heap);
	return(NULL);
    }
    return(heap);

}
