pcxEncode_getActualBufSizes (
    IP_XFORM_HANDLE  hXform,
    PDWORD           pdwMinInBufLen,
    PDWORD           pdwMinOutBufLen)
{
    PPCX_INST g;

    HANDLE_TO_PTR (hXform, g);
    *pdwMinInBufLen  = g->uBytesPerRawRow;
    *pdwMinOutBufLen = g->traits.iBitsPerPixel * g->uBytesPerPlane * 2;
    return IP_DONE;

    fatal_error:
    return IP_FATAL_ERROR;
}
