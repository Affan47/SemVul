Initialize( void *psWO )

{
    if( poWarper != NULL )
        delete poWarper;

    poWarper = new GDALWarpOperation();

    GDALWarpOptions* psWO_Dup = GDALCloneWarpOptions((GDALWarpOptions *) psWO);


    if (CSLFetchNameValue( psWO_Dup->papszWarpOptions, "INIT_DEST" ) == NULL)
        psWO_Dup->papszWarpOptions = CSLSetNameValue(psWO_Dup->papszWarpOptions, "INIT_DEST", "0");


    if( ((GDALWarpOptions *) psWO)->hSrcDS != NULL )
        GDALReferenceDataset( psWO_Dup->hSrcDS );

    CPLErr eErr = poWarper->Initialize( psWO_Dup );

    GDALDestroyWarpOptions(psWO_Dup);

    return eErr;
}
