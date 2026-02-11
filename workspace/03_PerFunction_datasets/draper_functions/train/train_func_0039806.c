amdlibCopyRawDataFile(const char      *srcFilename,
                                       const char      *dstFilename,
                                       amdlibERROR_MSG errMsg)
{
    char         fitsioMsg[256];
    fitsfile     *srcPtr,*dstPtr;
    int          status = 0;
    char *dst;
    dst=calloc(strlen(dstFilename)+2,sizeof(char));

    amdlibLogTrace("amdlibCopyRawDataFile()");

    if (fits_open_file(&srcPtr, srcFilename, READONLY, &status) != 0)
    {
        amdlibReturnFitsError(srcFilename);
    }

    sprintf(dst,"!%s",dstFilename);
    if (fits_create_file(&dstPtr, dst, &status) != 0)
    {
        amdlibReturnFitsError(dstFilename);
    }

    if (fits_copy_file(srcPtr, dstPtr, (int)1, (int)1,(int)1, &status) != 0)
    {
        amdlibSetErrMsg("Unable to copy Raw data file");
        return amdlibFAILURE;
    }

    if (fits_close_file(srcPtr, &status) != 0)
    {
        amdlibReturnFitsError(srcFilename);
    }
    if (fits_close_file(dstPtr, &status) != 0)
    {
        amdlibReturnFitsError(dstFilename);
    }
    return amdlibSUCCESS;

}
