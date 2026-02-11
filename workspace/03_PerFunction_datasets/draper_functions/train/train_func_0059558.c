ipGetOutputTraits (
    IP_HANDLE         hJob,
    LPIP_IMAGE_TRAITS pTraits)
{
    PINST           g;
    IP_IMAGE_TRAITS inTraits, outTraits;
    int        iXform;
    PXFORM_INFO     pXform;
    WORD        result;
    DWORD        dwHeaderLen;
    DWORD        dwInUsed, dwInNextPos;

    HANDLE_TO_PTR (hJob, g);
    INSURE (g->xfCount>=1);
    inTraits = g->xfArray[0].inTraits;

    for (iXform=0; iXform<g->xfCount; iXform++) {
        pXform = &(g->xfArray[iXform]);
        INSURE (pXform->eState == XS_NONEXISTENT);


        result = pXform->pXform->openXform (&pXform->hXform);
        INSURE (result == IP_DONE);

        result = pXform->pXform->setDefaultInputTraits (
                    pXform->hXform, &inTraits);
        INSURE (result == IP_DONE);

        result = pXform->pXform->setXformSpec (
                    pXform->hXform, pXform->aXformInfo);
        INSURE (result == IP_DONE);

        result = pXform->pXform->getHeaderBufSize (
                    pXform->hXform, &dwHeaderLen);
        INSURE (result == IP_DONE);
        INSURE (dwHeaderLen == 0);

        result = pXform->pXform->getActualTraits (
                    pXform->hXform,
                    0, NULL, &dwInUsed, &dwInNextPos,
                    &inTraits, &outTraits);
        INSURE (result & IP_DONE);

        result = pXform->pXform->closeXform (pXform->hXform);
        INSURE (result == IP_DONE);

        inTraits = outTraits;
        pXform->hXform = NULL;
    }

    *pTraits = outTraits;
    return IP_DONE;

    fatal_error:
    return IP_FATAL_ERROR;
}
