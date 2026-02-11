SkipFreeBackwards(struct HeapIterator *it)
{
    size_t idx = it->Heap->CurrentBlock * CHUNK_SIZE + it->Heap->BlockIndex;
    size_t start = idx;
    ListElement *le;
    char *p;

    p = it->Heap->Heap[it->BlockNumber];
    p += it->BlockPosition*it->Heap->ElementSize;
    le = (ListElement *)p;

    while (le->Next == INVALID_POINTER_VALUE) {
        idx--;
        if (it->Heap->BlockIndex > 0) {
            p -= it->Heap->ElementSize;
            it->BlockPosition--;
        }
        else {
            if (it->BlockNumber == 0)
                return -1;
            it->BlockNumber--;
            it->BlockPosition = CHUNK_SIZE-1;
            p = it->Heap->Heap[it->BlockNumber];
            p += (CHUNK_SIZE-1)*it->Heap->ElementSize;
        }
        le = (ListElement *)p;
    }
    if (idx == start) return 0;
    return 1;
}
