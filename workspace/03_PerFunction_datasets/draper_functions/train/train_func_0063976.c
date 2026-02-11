NewElement(PQueue *h)
{
    PQueueElement *e;

    e = iHeap.NewObject(h->Heap);
    if (e == NULL)
        return NULL;

    memset(e,0,sizeof(*e));
    e->Left = e;
    e->Right = e;
    return e;
}
