GetLayerByName( const char *pszName )

{
    char* pszTableName = NULL;
    char *pszGeomColumnName = NULL;
    char *pszSchemaName = NULL;

    if ( ! pszName )
        return NULL;

    int  i;

    int count = GetLayerCount();

    for( i = 0; i < count; i++ )
    {
        OGRPGTableLayer *poLayer = papoLayers[i];

        if( strcmp( pszName, poLayer->GetName() ) == 0 )
        {
            return poLayer;
        }
    }


    for( i = 0; i < count; i++ )
    {
        OGRPGTableLayer *poLayer = papoLayers[i];

        if( EQUAL( pszName, poLayer->GetName() ) )
        {
            return poLayer;
        }
    }

    char* pszNameWithoutBracket = CPLStrdup(pszName);
    char *pos = strchr(pszNameWithoutBracket, '(');
    if (pos != NULL)
    {
        *pos = '\0';
        pszGeomColumnName = CPLStrdup(pos+1);
        int len = strlen(pszGeomColumnName);
        if (len > 0)
            pszGeomColumnName[len - 1] = '\0';
    }

    pos = strchr(pszNameWithoutBracket, '.');
    if (pos != NULL)
    {
        *pos = '\0';
        pszSchemaName = CPLStrdup(pszNameWithoutBracket);
        pszTableName = CPLStrdup(pos + 1);
    }
    else
    {
        pszTableName = CPLStrdup(pszNameWithoutBracket);
    }
    CPLFree(pszNameWithoutBracket);
    pszNameWithoutBracket = NULL;

    OGRLayer* poLayer = NULL;

    if (pszSchemaName != NULL && osCurrentSchema == pszSchemaName &&
        pszGeomColumnName == NULL )
    {
        poLayer = GetLayerByName(pszTableName);
    }
    else
    {
        poLayer = OpenTable( osCurrentSchema, pszTableName,
                             pszSchemaName,
                             pszGeomColumnName,
                             bDSUpdate, TRUE, TRUE );
    }

    CPLFree(pszTableName);
    CPLFree(pszSchemaName);
    CPLFree(pszGeomColumnName);

    return poLayer;
}
