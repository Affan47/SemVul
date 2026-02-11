findPtrBlocks (StgPtr p, bdescr *bd, StgPtr arr[], int arr_size, int i)
{
    StgPtr q, r, end;
    for (; bd; bd = bd->link) {
        searched++;
        for (q = bd->start; q < bd->free; q++) {
            if (UNTAG_CLOSURE((StgClosure*)*q) == (StgClosure *)p) {
                if (i < arr_size) {
                    for (r = bd->start; r < bd->free; r = end) {

                        while (*r == 0) r++;
                        if (!LOOKS_LIKE_CLOSURE_PTR(r)) {
                            debugBelch("%p found at %p, no closure at %p\n",
                                       p, q, r);
                            break;
                        }
                        end = r + closure_sizeW((StgClosure*)r);
                        if (q < end) {
                            debugBelch("%p = ", r);
                            printClosure((StgClosure *)r);
                            arr[i++] = r;
                            break;
                        }
                    }
                    if (r >= bd->free) {
                        debugBelch("%p found at %p, closure?", p, q);
                    }
                } else {
                    return i;
                }
            }
        }
    }
    return i;
}
