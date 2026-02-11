amdlibReadImagingDataHdr
                                   (fitsfile           *filePtr,
                                    amdlibIMAGING_DATA *imagingData,
                                    amdlibERROR_MSG    errMsg)

{
    int         status = 0;
    char        fitsioMsg[256];

    amdlibLogTrace("amdlibReadImagingDataHdr()");


    memset(errMsg, '\0', sizeof(amdlibERROR_MSG));


    memset(imagingData, '\0', sizeof(amdlibIMAGING_DATA));


    if (fits_movnam_hdu(filePtr, BINARY_TBL, "IMAGING_DATA", 0, &status) != 0)
    {
        amdlibReturnFitsError("IMAGING_DATA");
    }


    if (fits_read_key(filePtr, TSTRING, "ORIGIN", &imagingData->origin,
                  NULL, &status) != 0)
    {
        status = 0;
    }
    if (fits_read_key(filePtr, TSTRING, "INSTRUME",
                      &imagingData->instrument, NULL, &status) != 0)
    {
        status = 0;
    }

    if (fits_read_key(filePtr, TDOUBLE, "MJD-OBS", &imagingData->dateObsMJD,
                      NULL, &status) != 0)
    {
        status = 0;
    }
    if (fits_read_key(filePtr, TSTRING, "DATE-OBS", &imagingData->dateObs,
                      NULL, &status) != 0)
    {
        status = 0;
    }
    if (fits_read_key(filePtr, TSTRING, "DATE", &imagingData->date,
                      NULL, &status) != 0)
    {
        status = 0;
    }

    if (fits_read_key(filePtr, TSTRING, "ESO DET DID",
                      &imagingData->detDictionaryId, NULL, &status) != 0)
    {
        status = 0;
    }
    if (fits_read_key(filePtr, TSTRING, "ESO DET ID", &imagingData->detId,
                      NULL, &status) != 0)
    {
        status = 0;
    }

    if (fits_read_key(filePtr, TINT, "NREGION", &imagingData->nbRegions,
                      NULL, &status) != 0)
    {
        amdlibReturnFitsError("NREGION");
    }

    if (fits_read_key(filePtr, TINT, "MAXTEL", &imagingData->maxTel,
                      NULL, &status) != 0)
    {
        status = 0;
    }
    if (fits_read_key(filePtr, TINT, "MAXINS", &imagingData->maxIns,
                      NULL, &status) != 0)
    {
        status = 0;
    }
    if (fits_read_key(filePtr, TINT, "MAXSTEP", &imagingData->maxStep,
                      NULL, &status) != 0)
    {
        status = 0;
    }
    return amdlibSUCCESS;
}
