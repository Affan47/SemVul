CollectADSMetadata()
{
    int nDSIndex, nNumDsr, nDSRSize;
    int nRecord;
    const char *pszDSName, *pszDSType, *pszDSFilename;
    const char *pszProduct;
    char *pszRecord;
    char szPrefix[128], szKey[128], szValue[1024];
    int i;
    CPLErr ret;
    const EnvisatRecordDescr *pRecordDescr = NULL;
    const EnvisatFieldDescr *pField;

    pszProduct = EnvisatFile_GetKeyValueAsString( hEnvisatFile, MPH,
                                                  "PRODUCT", "" );

    for( nDSIndex = 0;
         EnvisatFile_GetDatasetInfo( hEnvisatFile, nDSIndex,
                                     (char **) &pszDSName,
                                     (char **) &pszDSType,
                                     (char **) &pszDSFilename,
                                     NULL, NULL,
                                     &nNumDsr, &nDSRSize ) == SUCCESS;
         ++nDSIndex )
    {
        if( EQUALN(pszDSFilename,"NOT USED",8) || (nNumDsr <= 0) )
            continue;
        if( !EQUAL(pszDSType,"A") && !EQUAL(pszDSType,"G") )
            continue;

        for ( nRecord = 0; nRecord < nNumDsr; ++nRecord )
        {
            strncpy( szPrefix, pszDSName, sizeof(szPrefix) - 1);
            szPrefix[sizeof(szPrefix) - 1] = '\0';


            for( i = strlen(szPrefix)-1; i && szPrefix[i] == ' '; --i )
                szPrefix[i] = '\0';


            for( i = 0; szPrefix[i] != '\0'; i++ )
            {
                if( szPrefix[i] == ' ' )
                    szPrefix[i] = '_';
            }

            pszRecord = (char *) CPLMalloc(nDSRSize+1);

            if( EnvisatFile_ReadDatasetRecord( hEnvisatFile, nDSIndex, nRecord,
                                               pszRecord ) == FAILURE )
            {
                CPLFree( pszRecord );
                return;
            }

            pRecordDescr = EnvisatFile_GetRecordDescriptor(pszProduct, pszDSName);
            if (pRecordDescr)
            {
                pField = pRecordDescr->pFields;
                while ( pField && pField->szName )
                {
                    ret = EnvisatFile_GetFieldAsString(pszRecord, nDSRSize,
                                           pField, szValue);
                    if ( ret == CE_None )
                    {
                        if (nNumDsr == 1)
                            sprintf(szKey, "%s_%s", szPrefix, pField->szName);
                        else

                            sprintf(szKey, "%s_%d_%s", szPrefix, nRecord,
                                    pField->szName);
                        SetMetadataItem(szKey, szValue, "RECORDS");
                    }


                    ++pField;
                }
            }
            CPLFree( pszRecord );
        }
    }
}
