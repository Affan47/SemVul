UseHeap(List * L, const ContainerAllocator * m)
{
    if (L == NULL) {
        return NullPtrError("UseHeap");
    }
    if (L->Heap || L->count) {
        L->RaiseError("UseHeap", CONTAINER_ERROR_NOT_EMPTY);
        return CONTAINER_ERROR_NOT_EMPTY;
    }
    if (m == NULL)
        m = CurrentAllocator;
    L->Heap = iHeap.Create(L->ElementSize + sizeof(ListElement), m);
    return 1;
}
