_next(UV n, UINT *p, UINT *loc)
#endif
{
#ifndef USE_LINKEDLIST
    int i;
#endif
    bool is_done = FALSE;

    if (n <= 1)
        return TRUE;

#ifdef USE_LINKEDLIST

    if (ptr[n]->link != NULL) {
        pred[n]->link = ptr[n]->link;
        pred[n] = pred[n]->link;
        ptr[n]->link = pred[n]->link;
        pred[n]->link = ptr[n];
    } else {
        pred[n]->link = NULL;
        is_done = _next(n - 1, ptr_head, ptr, pred);
        ptr[n]->link = ptr_head->link;
        ptr_head->link = ptr[n];
        pred[n] = ptr_head;
    }
#else
    if (loc[n] < n) {

        p[loc[n]] = p[loc[n] + 1];
        p[++loc[n]] = n;
    } else {
        is_done = _next(n - 1, p, loc);

        for (i = n - 1; i >= 1; i--)
            p[i + 1] = p[i];

        p[1] = n;
        loc[n] = 1;
    }
#endif
    return is_done;
}
