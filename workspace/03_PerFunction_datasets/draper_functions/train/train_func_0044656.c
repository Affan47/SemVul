amdlibWriteOiWavelength(fitsfile         *filePtr,
                                         char             *insName,
                                         amdlibWAVELENGTH *wave,
                                         amdlibERROR_MSG  errMsg)
{
    int        status = 0;
    char       fitsioMsg[256];
    const int  tfields = 2;
    char       *ttype[] = {"EFF_WAVE", "EFF_BAND"};
    char       *tform[] = {"E", "E"};
    char       *tunit[] = {"m", "m"};
    char       extname[] = "OI_WAVELENGTH";
    int        revision = amdlib_OI_REVISION;
    int        i;
    amdlibDOUBLE      waveInM, bwInM;

    amdlibLogTrace("amdlibWriteOiWavelength()");


    if (fits_create_tbl (filePtr, BINARY_TBL, 1, tfields, ttype, tform, tunit,
                        extname, &status))
    {
        amdlibReturnFitsError("Creating Binary Table");
    }


    if (fits_write_key (filePtr, TINT, "OI_REVN", &revision,
                       "Revision number of the table definition", &status))
    {
        amdlibReturnFitsError("OI_REVN");
    }


    if (fits_write_key (filePtr, TSTRING, "INSNAME", insName,
                       "Instrument name", &status))
    {
        amdlibReturnFitsError("INSNAME");
    }

    for (i = 1; i <= wave->nbWlen; i ++)
    {
        waveInM = (wave->wlen[i-1]) * amdlibNM_TO_M;
        bwInM = (wave->bandwidth[i-1]) * amdlibNM_TO_M;

        if (fits_write_col (filePtr, TDOUBLE, 1, i, 1, 1, &waveInM, &status))
        {
            amdlibReturnFitsError("EFFective_WAVElengh");
        }


        if (fits_write_col (filePtr, TDOUBLE, 2, i, 1, 1, &bwInM, &status))
        {
            amdlibReturnFitsError("EFFective_BANDwidth");
        }
    }

    return amdlibSUCCESS;
}
