scavenge_mut_arr_ptrs_marked (StgMutArrPtrs *a)
{
    W_ m;
    StgPtr p, q;
    rtsBool any_failed;

    any_failed = rtsFalse;
    for (m = 0; m < mutArrPtrsCards(a->ptrs); m++)
    {
        if (*mutArrPtrsCard(a,m) != 0) {
            p = (StgPtr)&a->payload[m << MUT_ARR_PTRS_CARD_BITS];
            q = stg_min(p + (1 << MUT_ARR_PTRS_CARD_BITS),
                        (StgPtr)&a->payload[a->ptrs]);
            for (; p < q; p++) {
                evacuate((StgClosure**)p);
            }
            if (gct->failed_to_evac) {
                any_failed = rtsTrue;
                gct->failed_to_evac = rtsFalse;
            } else {
                *mutArrPtrsCard(a,m) = 0;
            }
        }
    }

    gct->failed_to_evac = any_failed;
    return (StgPtr)a + mut_arr_ptrs_sizeW(a);
}
