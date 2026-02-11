Create
(
	const char* pszFilename,
    int nXSize, int nYSize, int nBands,
    GDALDataType eType, char** papszOptions
)
{
    TerragenDataset* poDS = new TerragenDataset();

    poDS->eAccess = GA_Update;

	poDS->m_pszFilename = CPLStrdup(pszFilename);


    const char* pszValue = CSLFetchNameValue(
		papszOptions,"MINUSERPIXELVALUE");
    if( pszValue != NULL )
        poDS->m_dLogSpan[0] = atof( pszValue );

    pszValue = CSLFetchNameValue(
		papszOptions,"MAXUSERPIXELVALUE");
    if( pszValue != NULL )
        poDS->m_dLogSpan[1] = atof( pszValue );


	if( poDS->m_dLogSpan[1] <= poDS->m_dLogSpan[0] )
	{
        CPLError( CE_Failure, CPLE_AppDefined,
              "Inverted, flat, or unspecified span for Terragen file." );

		delete poDS;
        return NULL;
	}

    if( eType != GDT_Float32 )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
              "Attempt to create Terragen dataset with a non-float32\n"
              "data type (%s).\n",
              GDALGetDataTypeName(eType) );

		delete poDS;
        return NULL;
    }


    if( nBands != 1 )
    {
        CPLError( CE_Failure, CPLE_NotSupported,
                  "Terragen driver doesn't support %d bands. Must be 1.\n",
                  nBands );

		delete poDS;
        return NULL;
    }


    poDS->m_fp = VSIFOpenL( pszFilename, "wb+" );

    if( poDS->m_fp == NULL )
    {
        CPLError( CE_Failure, CPLE_OpenFailed,
                  "Attempt to create file `%s' failed.\n",
                  pszFilename );
		delete poDS;
        return NULL;
    }

    poDS->nRasterXSize = nXSize;
    poDS->nRasterYSize = nYSize;


    poDS->SetBand( 1, new TerragenRasterBand( poDS ) );


    return (GDALDataset *) poDS;

}
