DefaultRename( const char * pszNewName,
                                  const char *pszOldName )

{


    GDALDatasetH hDS = (GDALDataset *) GDALOpen(pszOldName,GA_ReadOnly);

    if( hDS == NULL )
    {
        if( CPLGetLastErrorNo() == 0 )
            CPLError( CE_Failure, CPLE_OpenFailed,
                      "Unable to open %s to obtain file list.", pszOldName );

        return CE_Failure;
    }

    char **papszFileList = GDALGetFileList( hDS );

    GDALClose( hDS );

    if( CSLCount( papszFileList ) == 0 )
    {
        CPLError( CE_Failure, CPLE_NotSupported,
                  "Unable to determine files associated with %s,\n"
                  "rename fails.", pszOldName );

        return CE_Failure;
    }


    CPLErr eErr = CE_None;
    int i;
    char **papszNewFileList =
        CPLCorrespondingPaths( pszOldName, pszNewName, papszFileList );

    if( papszNewFileList == NULL )
        return CE_Failure;

    for( i = 0; papszFileList[i] != NULL; i++ )
    {
        if( CPLMoveFile( papszNewFileList[i], papszFileList[i] ) != 0 )
        {
            eErr = CE_Failure;

            for( --i; i >= 0; i-- )
                CPLMoveFile( papszFileList[i], papszNewFileList[i] );
            break;
        }
    }

    CSLDestroy( papszNewFileList );
    CSLDestroy( papszFileList );

    return eErr;
}
