crop_getActualTraits (
    IP_XFORM_HANDLE  hXform,
    DWORD            dwInputAvail,
    PBYTE            pbInputBuf,
    PDWORD           pdwInputUsed,
    PDWORD           pdwInputNextPos,
    PIP_IMAGE_TRAITS pInTraits,
    PIP_IMAGE_TRAITS pOutTraits)
{
    PCROP_INST g;
    int        left, right, shift;
    int        inWidth, outWidth;
    int        bpp;
    long       actualOut, maxOut;

    HANDLE_TO_PTR (hXform, g);


    *pdwInputUsed    = 0;
    *pdwInputNextPos = 0;


    bpp      = g->traits.iBitsPerPixel;
    left     = g->dwLeft;
    right    = g->dwRight;
    inWidth  = g->traits.iPixelsPerRow;
    outWidth = inWidth - left - right;
    INSURE (outWidth >= 0);

    if (bpp == 1) {

        shift = ((left+4) & ~7) - left;
        left  += shift;
        right += shift;
    }

    g->dwInBytesPerRow  = (bpp*inWidth  + 7) / 8;
    g->dwOutBytesPerRow = (bpp*outWidth + 7) / 8;
    g->dwLeftCropBytes  = (bpp*left     + 7) / 8;


    *pInTraits  = g->traits;
    *pOutTraits = g->traits;
    pOutTraits->iPixelsPerRow = outWidth;


    if (pInTraits->lNumRows > 0) {
        maxOut = g->dwMaxOutRows;
        actualOut = pInTraits->lNumRows - (long)g->dwTop;
        INSURE (actualOut >= 0);
        pOutTraits->lNumRows = actualOut<maxOut ? actualOut : maxOut;
    }

    return IP_DONE | IP_READY_FOR_DATA;

    fatal_error:
    return IP_FATAL_ERROR;
}
