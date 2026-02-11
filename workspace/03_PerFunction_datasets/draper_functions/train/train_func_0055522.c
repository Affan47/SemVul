Create( const char *pszName, char** papszOptions )

{
    const char *pszConf;
    const char *pszExtension;

    if( _pszName ) CPLFree(_pszName);
    _papszOptions = CSLDuplicate( papszOptions );

    pszConf= CSLFetchNameValue(papszOptions,"CONFIG");
    if( pszConf != NULL )
    {
      _pszGCT = CPLStrdup(pszConf);
    }

    _pszExt = (char *)CSLFetchNameValue(papszOptions,"EXTENSION");
    pszExtension = CSLFetchNameValue(papszOptions,"EXTENSION");
    if( pszExtension == NULL )
    {
        _pszExt = CPLStrdup(CPLGetExtension(pszName));
    }
    else
    {
        _pszExt = CPLStrdup(pszExtension);
    }

    if( strlen(_pszExt) == 0 )
    {
        if( VSIMkdir( pszName, 0755 ) != 0 )
        {
            CPLError( CE_Failure, CPLE_AppDefined,
                      "Directory %s already exists"
                      " as geoconcept datastore or"
                      " is made up of a non existing list of directories.",
                      pszName );

            return FALSE;
        }
        _pszDirectory = CPLStrdup( pszName );
        CPLFree(_pszExt);
        _pszExt = CPLStrdup("gxt");
        char *pszbName = CPLStrdup(CPLGetBasename( pszName ));
        if (strlen(pszbName)==0) {
            CPLFree(pszbName);
            char *pszNameDup= CPLStrdup(pszName);
            pszNameDup[strlen(pszName)-2] = '\0';
            pszbName = CPLStrdup(CPLGetBasename( pszNameDup ));
            CPLFree(pszNameDup);
        }
        _pszName = CPLStrdup((char *)CPLFormFilename( _pszDirectory, pszbName, NULL ));
        CPLFree(pszbName);
    }
    else
    {
        _pszDirectory = CPLStrdup( CPLGetPath(pszName) );
        _pszName = CPLStrdup( pszName );
    }


    _bSingleNewFile = TRUE;

    if( !LoadFile( "wt" ) )
    {
        CPLDebug( "GEOCONCEPT",
                  "Failed to create Geoconcept %s.",
                  pszName );

        return FALSE;
    }

    return TRUE;
}
