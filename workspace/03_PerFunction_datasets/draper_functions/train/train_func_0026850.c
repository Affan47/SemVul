Open( GDALOpenInfo * poOpenInfo )
{
    if( !Identify(poOpenInfo) )
        return NULL;


    NWT_GRDDataset *poDS;

    poDS = new NWT_GRDDataset();

    poDS->fp = VSIFOpenL(poOpenInfo->pszFilename, "rb");
    if (poDS->fp == NULL)
    {
        delete poDS;
        return NULL;
    }


    VSIFSeekL( poDS->fp, 0, SEEK_SET );
    VSIFReadL( poDS->abyHeader, 1, 1024, poDS->fp );
    poDS->pGrd = (NWT_GRID *) malloc(sizeof(NWT_GRID));

    poDS->pGrd->fp = poDS->fp;

    if (!nwt_ParseHeader( poDS->pGrd, (char *) poDS->abyHeader ) ||
        !GDALCheckDatasetDimensions(poDS->pGrd->nXSide, poDS->pGrd->nYSide) )
    {
        delete poDS;
        return NULL;
    }

    poDS->nRasterXSize = poDS->pGrd->nXSide;
    poDS->nRasterYSize = poDS->pGrd->nYSide;


  nwt_LoadColors( poDS->ColorMap, 4096, poDS->pGrd );


    poDS->SetBand( 1, new NWT_GRDRasterBand( poDS, 1 ) );
    poDS->SetBand( 2, new NWT_GRDRasterBand( poDS, 2 ) );
    poDS->SetBand( 3, new NWT_GRDRasterBand( poDS, 3 ) );
    poDS->SetBand( 4, new NWT_GRDRasterBand( poDS, 4 ) );


    poDS->SetDescription( poOpenInfo->pszFilename );
    poDS->TryLoadXML();


    poDS->oOvManager.Initialize( poDS, poOpenInfo->pszFilename, poOpenInfo->papszSiblingFiles );

    return (poDS);
}
