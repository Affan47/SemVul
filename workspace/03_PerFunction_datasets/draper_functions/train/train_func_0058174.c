NITFDESExtractShapefile(NITFDES* psDES, const char* pszRadixFileName)
{
    NITFSegmentInfo* psSegInfo;
    const char* apszExt[3];
    int anOffset[4];
    int iShpFile;
    char* pszFilename;

    if ( CSLFetchNameValue(psDES->papszMetadata, "NITF_SHAPE_USE") == NULL )
        return FALSE;

    psSegInfo = psDES->psFile->pasSegmentInfo + psDES->iSegment;

    apszExt[0] = CSLFetchNameValue(psDES->papszMetadata, "NITF_SHAPE1_NAME");
    anOffset[0] = atoi(CSLFetchNameValue(psDES->papszMetadata, "NITF_SHAPE1_START"));
    apszExt[1] = CSLFetchNameValue(psDES->papszMetadata, "NITF_SHAPE2_NAME");
    anOffset[1] = atoi(CSLFetchNameValue(psDES->papszMetadata, "NITF_SHAPE2_START"));
    apszExt[2] = CSLFetchNameValue(psDES->papszMetadata, "NITF_SHAPE3_NAME");
    anOffset[2] = atoi(CSLFetchNameValue(psDES->papszMetadata, "NITF_SHAPE3_START"));
    anOffset[3] = (int) psSegInfo->nSegmentSize;

    for(iShpFile = 0; iShpFile < 3; iShpFile ++)
    {
        if (!EQUAL(apszExt[iShpFile], "SHP") &&
            !EQUAL(apszExt[iShpFile], "SHX") &&
            !EQUAL(apszExt[iShpFile], "DBF"))
            return FALSE;

        if (anOffset[iShpFile] < 0 ||
            anOffset[iShpFile] >= anOffset[iShpFile+1])
            return FALSE;
    }

    pszFilename = (char*) VSIMalloc(strlen(pszRadixFileName) + 4 + 1);
    if (pszFilename == NULL)
        return FALSE;

    for(iShpFile = 0; iShpFile < 3; iShpFile ++)
    {
        VSILFILE* fp;
        GByte* pabyBuffer;
        int nSize = anOffset[iShpFile+1] - anOffset[iShpFile];

        pabyBuffer = (GByte*) VSIMalloc(nSize);
        if (pabyBuffer == NULL)
        {
            VSIFree(pszFilename);
            return FALSE;
        }

        VSIFSeekL(psDES->psFile->fp, psSegInfo->nSegmentStart + anOffset[iShpFile], SEEK_SET);
        if (VSIFReadL(pabyBuffer, 1, nSize, psDES->psFile->fp) != nSize)
        {
            VSIFree(pabyBuffer);
            VSIFree(pszFilename);
            return FALSE;
        }

        sprintf(pszFilename, "%s.%s", pszRadixFileName, apszExt[iShpFile]);
        fp = VSIFOpenL(pszFilename, "wb");
        if (fp == NULL)
        {
            VSIFree(pabyBuffer);
            VSIFree(pszFilename);
            return FALSE;
        }

        VSIFWriteL(pabyBuffer, 1, nSize, fp);
        VSIFCloseL(fp);
        VSIFree(pabyBuffer);
    }

    VSIFree(pszFilename);

    return TRUE;
}
