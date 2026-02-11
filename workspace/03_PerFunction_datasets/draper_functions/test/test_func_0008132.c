pad_convert (
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
    PPAD_INST g;
    BOOL      bWhiteRow;

    HANDLE_TO_PTR (hXform, g);
    bWhiteRow = FALSE;


    if (pbInputBuf == NULL) {
        PRINT (_T("pad_convert: Told to flush.\n"), 0, 0);

        if (g->dwInRows < g->dwMinInRows) {

            bWhiteRow = TRUE;
            g->dwInRows += 1;
        } else if (g->dwBottom > 0) {

            bWhiteRow = TRUE;
            g->dwBottom -= 1;
        } else {

            *pdwInputUsed = *pdwOutputUsed = 0;
            *pdwInputNextPos  = g->dwInNextPos;
            *pdwOutputThisPos = g->dwOutNextPos;
            return IP_DONE;
        }
    } else if (g->dwOutRows < g->dwTop) {

        bWhiteRow = TRUE;
    }


    INSURE (bWhiteRow || (dwInputAvail >= g->dwInBytesPerRow));
    INSURE (dwOutputAvail >= g->dwOutBytesPerRow);

    if (bWhiteRow)
        memset (pbOutputBuf, g->bPadVal, g->dwOutBytesPerRow);
    else {
        BYTE *p = pbOutputBuf;
        memset (p, g->bPadVal, g->dwLeftPadBytes);
        p += g->dwLeftPadBytes;
        memcpy (p, pbInputBuf, g->dwInBytesPerRow);
        p += g->dwInBytesPerRow;
        memset (p, g->bPadVal, g->dwRightPadBytes);

        g->dwInRows += 1;
        *pdwInputUsed     = g->dwInBytesPerRow;
        g->dwInNextPos   += g->dwInBytesPerRow;
    }

    g->dwOutRows += 1;
    *pdwInputNextPos  = g->dwInNextPos;
    *pdwOutputUsed    = g->dwOutBytesPerRow;
    *pdwOutputThisPos = g->dwOutNextPos;
    g->dwOutNextPos  += g->dwOutBytesPerRow;

    return (bWhiteRow ? 0 : IP_CONSUMED_ROW) |
           IP_PRODUCED_ROW |
           (g->dwOutRows < g->dwTop ? 0 : IP_READY_FOR_DATA);

    fatal_error:
    return IP_FATAL_ERROR;
}
