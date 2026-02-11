Seek(Iterator * it, size_t idx)
{
    struct ListIterator *li = (struct ListIterator *) it;
    ListElement    *rvp;

    if (it == NULL) {
        NullPtrError("Seek");
        return NULL;
    }

	if (li->Magic != LIST_MAGIC_NUMBER) {
		iError.RaiseError("List.Seek",CONTAINER_ERROR_WRONG_ITERATOR);
		return NULL;
	}
    if (li->L->count == 0)
        return NULL;
    rvp = li->L->First;
    if (idx == 0) {
        li->index = 0;
        li->Current = li->L->First;
    } else if (idx >= li->L->count - 1) {
        li->index = li->L->count - 1;
        li->Current = li->L->Last;
    } else {
        li->index = idx;
        while (idx > 0) {
            rvp = rvp->Next;
            idx--;
        }
        li->Current = rvp;
    }
    return li->Current;
}
