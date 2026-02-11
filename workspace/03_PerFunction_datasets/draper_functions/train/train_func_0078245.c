gray2bi_convert (
    IP_XFORM_HANDLE hXform,
    DWORD           dwInputAvail,
    PBYTE           pbInputBuf,
    PDWORD          pdwInputUsed,
    PDWORD          pdwInputNextPos,
    DWORD           dwOutputAvail,
    PBYTE           pbOutputBuf,
    PDWORD          pdwOutputUsed,
    PDWORD          pdwOutputThisPos)
{
    PG2B_INST g;
    int       inBytes, outBytes;

    HANDLE_TO_PTR (hXform, g);


    if (pbInputBuf == NULL) {
        PRINT (_T("gray2bi_convert: Told to flush.\n"), 0, 0);
        *pdwInputUsed = *pdwOutputUsed = 0;
        *pdwInputNextPos  = g->dwInNextPos;
        *pdwOutputThisPos = g->dwOutNextPos;
        return IP_DONE;
    }


    inBytes  = g->inTraits.iPixelsPerRow;
    outBytes = (inBytes + 7) / 8;
    INSURE (dwInputAvail  >= (DWORD)inBytes );
    INSURE (dwOutputAvail >= (DWORD)outBytes);

    if (g->bThreshold == 0) {
        INSURE (g->pErrBuf != NULL);
        diffuseRow (inBytes, g->pErrBuf, pbInputBuf, pbOutputBuf);
    } else
        thresholdRow (inBytes, g->bThreshold, pbInputBuf, pbOutputBuf);

    *pdwInputUsed     = inBytes;
    g->dwInNextPos   += inBytes;
    *pdwInputNextPos  = g->dwInNextPos;

    *pdwOutputUsed    = outBytes;
    *pdwOutputThisPos = g->dwOutNextPos;
    g->dwOutNextPos  += outBytes;

    g->dwRowsDone += 1;

    return IP_CONSUMED_ROW | IP_PRODUCED_ROW | IP_READY_FOR_DATA;

    fatal_error:
    return IP_FATAL_ERROR;
}
