ensRepeatmaskedsliceNewCpy(
    const EnsPRepeatmaskedslice rmslice)
{
    void **keyarray = NULL;
    void **valarray = NULL;

    register ajuint i = 0U;

    EnsERepeatMaskType *Pmsktyp = NULL;

    AjIList iter = NULL;

    AjPStr key = NULL;

    EnsPRepeatmaskedslice pthis = NULL;

    if (!rmslice)
        return NULL;

    AJNEW0(pthis);

    pthis->Slice = ensSliceNewRef(rmslice->Slice);


    if (rmslice->Analysisnames)
    {
        pthis->Analysisnames = ajListstrNew();

        iter = ajListIterNew(rmslice->Analysisnames);

        while (!ajListIterDone(iter))
        {
            key = (AjPStr) ajListIterGet(iter);

            if (key && ajStrGetLen(key))
                ajListPushAppend(pthis->Analysisnames,
                                 (void *) ajStrNewS(key));
        }

        ajListIterDel(&iter);
    }


    if (rmslice->Masking)
    {
        pthis->Masking = ajTablestrNew(0U);

        ajTableSetDestroyvalue(pthis->Masking, &ajMemFree);

        ajTableToarrayKeysValues(rmslice->Masking, &keyarray, &valarray);

        for (i = 0U; keyarray[i]; i++)
        {
            key = ajStrNewS((AjPStr) keyarray[i]);

            AJNEW0(Pmsktyp);

            *Pmsktyp = *((EnsERepeatMaskType *) valarray[i]);

            ajTablePut(pthis->Masking, (void *) key, (void *) Pmsktyp);
        }

        AJFREE(keyarray);
        AJFREE(valarray);
    }

    pthis->Use = 1U;

    return pthis;
}
