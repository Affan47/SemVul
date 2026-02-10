readTrueHeading(double* pdfTrueHeading, int iToken, const char* pszTokenDesc)
{
    int bRet = readDoubleWithBounds(pdfTrueHeading, iToken, pszTokenDesc, -180., 360.);
    if (bRet)
    {
        if (*pdfTrueHeading < 0.)
            *pdfTrueHeading += 180.;
    }
    return bRet;
}
