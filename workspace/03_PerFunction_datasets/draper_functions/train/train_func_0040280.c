ntrHeapify(
  NtrHeap *heap,
  int i)
{
    int smallest;
    int left = LEFT(i);
    int right = RIGHT(i);
    int nslots = heap->nslots;
    NtrHeapSlot *slots = heap->slots;
    int key = KEY(slots,i);

    if (left < nslots && KEY(slots,left) < key) {
	smallest = left;
    } else {
	smallest = i;
    }
    if (right < nslots && KEY(slots,right) < KEY(slots,smallest)) {
	smallest = right;
    }
    if (smallest != i) {
	void *item = ITEM(slots,i);
	KEY(slots,i) = KEY(slots,smallest);
	ITEM(slots,i) = ITEM(slots,smallest);
	KEY(slots,smallest) = key;
	ITEM(slots,smallest) = item;
	ntrHeapify(heap,smallest);
    }

    return;

}
