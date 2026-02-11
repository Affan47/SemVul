dglHeapInsertMax(dglHeap_s * pheap,
		     long key, unsigned char flags, dglHeapData_u value)
{
    long i;

    if (pheap->index >= pheap->count - 1) {
	pheap->count += pheap->block;
	if ((pheap->pnode =
	     realloc(pheap->pnode,
		     sizeof(dglHeapNode_s) * pheap->count)) == NULL)
	    return -1;
    }

    i = ++pheap->index;

    while (i != 1 && key > pheap->pnode[i / 2].key) {
	pheap->pnode[i] = pheap->pnode[i / 2];
	i /= 2;
    }

    pheap->pnode[i].key = key;
    pheap->pnode[i].flags = flags;
    pheap->pnode[i].value = value;

    return i;
}
