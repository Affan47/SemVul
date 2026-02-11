pcxEncode_convert (
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
    PPCX_INST g;
    UINT      out_used = 0;

    HANDLE_TO_PTR (hXform, g);


    if (! g->fDidHeader) {
        g->fDidHeader = TRUE;
        *pdwInputUsed    = 0;
        *pdwInputNextPos = 0;
        return outputHeader (g, dwOutputAvail, pbOutputBuf,
                             pdwOutputUsed, pdwOutputThisPos);
    }


    if (pbInputBuf == NULL) {
        PRINT (_T("pcx_encode_convert_row: Told to flush.\n"), 0, 0);
        if (g->traits.lNumRows < 0) {


            g->traits.lNumRows = g->uRowsDone;
            *pdwInputUsed    = 0;
            *pdwInputNextPos = g->dwInNextPos;
            return outputHeader (g, dwOutputAvail, pbOutputBuf,
                                 pdwOutputUsed, pdwOutputThisPos);
        }

        *pdwInputUsed = *pdwOutputUsed = 0;
        *pdwInputNextPos  = g->dwInNextPos;
        *pdwOutputThisPos = g->dwOutNextPos;
        return IP_DONE;
    }


    switch (g->traits.iBitsPerPixel) {
        case 1:  out_used = encode_1 (g, pbInputBuf, pbOutputBuf);
                 break;

        case 4:  out_used = encode_4 (g, pbInputBuf, pbOutputBuf);
                 break;
        #if 0
        case 8:  out_used = encode_8 (g, pbInputBuf, pbOutputBuf);
                 break;
        #endif
    }

    INSURE (dwInputAvail  >= g->uBytesPerRawRow);
    INSURE (dwOutputAvail >= out_used);

    g->dwInNextPos   += g->uBytesPerRawRow;
    *pdwInputNextPos  = g->dwInNextPos;
    *pdwInputUsed     = g->uBytesPerRawRow;
    *pdwOutputUsed    = out_used;
    *pdwOutputThisPos = g->dwOutNextPos;
    g->dwOutNextPos  += out_used;

    g->uRowsDone += 1;

    PRINT (_T("pcx_encode_convert_row: Returning, out used = %d\n"), out_used, 0);
    return IP_CONSUMED_ROW | IP_PRODUCED_ROW | IP_READY_FOR_DATA;

    fatal_error:
    return IP_FATAL_ERROR;
}
