IsScanlineDirty(byte* pScanline, int iWidth)
{
    byte * pCurr = pScanline;
    byte * pStop = pCurr + iWidth;

    while (pStop-pCurr)
    {
        if (*pCurr - 0xFF)
        {

            return 1;
        }
        ++pCurr;
    }
    return 0;
}
