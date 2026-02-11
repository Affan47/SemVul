Identify( GDALOpenInfo *poOpenInfo )
{
    if (poOpenInfo->fp == NULL || poOpenInfo->nHeaderBytes < 260)
    {
        if( poOpenInfo->bIsDirectory )
        {
            CPLString osFilename =
                CPLFormCIFilename( poOpenInfo->pszFilename, CPLGetFilename( poOpenInfo->pszFilename ), "xml" );


            if (!(EQUALN(CPLGetBasename( osFilename ), "TSX1_SAR", 8) ||
                  EQUALN(CPLGetBasename( osFilename ), "TDX1_SAR", 8)))
                return 0;

            VSIStatBufL sStat;
            if( VSIStatL( osFilename, &sStat ) == 0 )
                return 1;
        }

        return 0;
    }


    if (!(EQUALN(CPLGetBasename( poOpenInfo->pszFilename ), "TSX1_SAR", 8) ||
          EQUALN(CPLGetBasename( poOpenInfo->pszFilename ), "TDX1_SAR", 8)))
        return 0;


    if (!EQUALN((char *)poOpenInfo->pabyHeader, "<level1Product", 14))
        return 0;

    return 1;
}
