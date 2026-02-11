GTIFF_CanCopyFromJPEG(GDALDataset* poSrcDS, char** &papszCreateOptions)
{
    poSrcDS = GetUnderlyingDataset(poSrcDS);
    if (poSrcDS == NULL)
        return FALSE;
    if (poSrcDS->GetDriver() == NULL)
        return FALSE;
    if (!EQUAL(GDALGetDriverShortName(poSrcDS->GetDriver()), "JPEG"))
        return FALSE;

    const char* pszCompress = CSLFetchNameValue(papszCreateOptions, "COMPRESS");
    if (pszCompress == NULL || !EQUAL(pszCompress, "JPEG"))
        return FALSE;

    int nBlockXSize = atoi(CSLFetchNameValueDef(papszCreateOptions, "BLOCKXSIZE", "0"));
    int nBlockYSize = atoi(CSLFetchNameValueDef(papszCreateOptions, "BLOCKYSIZE", "0"));
    int nMCUSize = 8;
    const char* pszSrcColorSpace =
        poSrcDS->GetMetadataItem("SOURCE_COLOR_SPACE", "IMAGE_STRUCTURE");
    if (pszSrcColorSpace != NULL && EQUAL(pszSrcColorSpace, "YCbCr"))
        nMCUSize = 16;
    else if (pszSrcColorSpace != NULL &&
        (EQUAL(pszSrcColorSpace, "CMYK") || EQUAL(pszSrcColorSpace, "YCbCrK")))
        return FALSE;

    int     nXSize = poSrcDS->GetRasterXSize();
    int     nYSize = poSrcDS->GetRasterYSize();
    int     nBands = poSrcDS->GetRasterCount();

    const char* pszPhotometric = CSLFetchNameValue(papszCreateOptions, "PHOTOMETRIC");
    int bCompatiblePhotometric = (
            pszPhotometric == NULL ||
            (nMCUSize == 16 && EQUAL(pszPhotometric, "YCbCr")) ||
            (nMCUSize == 8 && EQUAL(pszPhotometric, "RGB") && nBands == 3) ||
            (nMCUSize == 8 && EQUAL(pszPhotometric, "MINISBLACK") && nBands == 1) );
    if (!bCompatiblePhotometric)
        return FALSE;

    if ( (nBlockXSize == nXSize || (nBlockXSize % nMCUSize) == 0) &&
         (nBlockYSize == nYSize || (nBlockYSize % nMCUSize) == 0) &&
         poSrcDS->GetRasterBand(1)->GetRasterDataType() == GDT_Byte &&
         CSLFetchNameValue(papszCreateOptions, "NBITS") == NULL &&
         CSLFetchNameValue(papszCreateOptions, "JPEG_QUALITY") == NULL &&
         bCompatiblePhotometric )
    {
        if (nMCUSize == 16 && pszPhotometric == NULL)
            papszCreateOptions = CSLSetNameValue(papszCreateOptions, "PHOTOMETRIC", "YCBCR");
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
