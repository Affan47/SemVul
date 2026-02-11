popWSDeque (WSDeque *q)
{


    StgWord t, b;
    long  currSize;
    void * removed;

    ASSERT_WSDEQUE_INVARIANTS(q);

    b = q->bottom;


    b--;
    q->bottom = b;


    store_load_barrier();

    t = q->top;


    q->topBound = t;
    currSize = (long)b - (long)t;
    if (currSize < 0) {

        q->bottom = t;
        return NULL;
    }


    removed = q->elements[b & q->moduloSize];

    if (currSize > 0) {

        return removed;
    }


    if ( !(CASTOP(&(q->top),t,t+1)) ) {
        removed = NULL;
    }
    q->bottom = t+1;
    q->topBound = t+1;

    ASSERT_WSDEQUE_INVARIANTS(q);
    ASSERT(q->bottom >= q->top);


    return removed;
}
