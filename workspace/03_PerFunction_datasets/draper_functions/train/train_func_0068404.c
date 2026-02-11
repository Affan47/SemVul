insert_head(PyWeakReference *newref, PyWeakReference **list)
{
    PyWeakReference *next = *list;

    newref->wr_prev = NULL;
    newref->wr_next = next;
    if (next != NULL)
        next->wr_prev = newref;
    *list = newref;
}
