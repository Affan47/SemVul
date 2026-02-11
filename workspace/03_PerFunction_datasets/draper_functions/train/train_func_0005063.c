GDALCopyDatasetFiles( GDALDriverH hDriver,
                                         const char * pszNewName,
                                         const char * pszOldName )

{
    if( hDriver == NULL )
        hDriver = GDALIdentifyDriver( pszOldName, NULL );

    if( hDriver == NULL )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "No identifiable driver for %s.",
                  pszOldName );
        return CE_Failure;
    }

    return ((GDALDriver *) hDriver)->CopyFiles( pszNewName, pszOldName );
}
