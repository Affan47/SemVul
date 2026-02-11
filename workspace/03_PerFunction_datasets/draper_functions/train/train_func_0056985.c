Ntr_HeapInsert(
  NtrHeap *heap,
  void *item,
  int key)
{
    NtrHeapSlot *slots;
    int i = heap->nslots;

    if (i == heap->size && !ntrHeapResize(heap)) return(0);
    slots = heap->slots;
    heap->nslots++;
    while (i > 0 && KEY(slots,PARENT(i)) > key) {
	ITEM(slots,i) = ITEM(slots,PARENT(i));
	KEY(slots,i) = KEY(slots,PARENT(i));
	i = PARENT(i);
    }
    ITEM(slots,i) = item;
    KEY(slots,i) = key;
    return(1);

}
