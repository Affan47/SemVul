dewarpaDestroy(L_DEWARPA  **pdewa)
{
l_int32     i;
L_DEWARP   *dew;
L_DEWARPA  *dewa;

    PROCNAME("dewarpaDestroy");

    if (pdewa == NULL) {
        L_WARNING("ptr address is null!\n", procName);
        return;
    }
    if ((dewa = *pdewa) == NULL)
        return;

    for (i = 0; i < dewa->nalloc; i++) {
        if ((dew = dewa->dewarp[i]) != NULL)
            dewarpDestroy(&dew);
        if ((dew = dewa->dewarpcache[i]) != NULL)
            dewarpDestroy(&dew);
    }
    numaDestroy(&dewa->namodels);
    numaDestroy(&dewa->napages);

    FREE(dewa->dewarp);
    FREE(dewa->dewarpcache);
    FREE(dewa);
    *pdewa = NULL;
    return;
}
