TranslateNASSchema( GMLFeatureClass *poClass )

{
    OGRNASLayer *poLayer;
    OGRwkbGeometryType eGType
        = (OGRwkbGeometryType) poClass->GetGeometryType();

    if( poClass->GetFeatureCount() == 0 )
        eGType = wkbUnknown;


    const char* pszSRSName = poClass->GetSRSName();
    OGRSpatialReference* poSRS = NULL;
    if (pszSRSName)
    {
        int i;

        poSRS = new OGRSpatialReference();

        const char *pszHandle = strrchr( pszSRSName, ':' );
        if( pszHandle != NULL )
            pszHandle += 1;

        for( i = 0; apszURNNames[i*2+0] != NULL; i++ )
        {
            const char *pszTarget = apszURNNames[i*2+0];
            int nTLen = strlen(pszTarget);


            if( pszTarget[nTLen-1] == '*' )
            {
                if( EQUALN(pszTarget,pszHandle,nTLen-1) )
                    pszSRSName = apszURNNames[i*2+1];
            }
            else
            {
                if( EQUAL(pszTarget,pszHandle) )
                    pszSRSName = apszURNNames[i*2+1];
            }
        }

        if (poSRS->SetFromUserInput(pszSRSName) != OGRERR_NONE)
        {
            CPLDebug( "NAS", "Failed to translate srsName='%s'",
                      pszSRSName );
            delete poSRS;
            poSRS = NULL;
        }
    }


    poLayer = new OGRNASLayer( poClass->GetName(), poSRS, eGType, this );
    delete poSRS;


    for( int iField = 0; iField < poClass->GetPropertyCount(); iField++ )
    {
        GMLPropertyDefn *poProperty = poClass->GetProperty( iField );
        OGRFieldType eFType;

        if( poProperty->GetType() == GMLPT_Untyped )
            eFType = OFTString;
        else if( poProperty->GetType() == GMLPT_String )
            eFType = OFTString;
        else if( poProperty->GetType() == GMLPT_Integer )
            eFType = OFTInteger;
        else if( poProperty->GetType() == GMLPT_Real )
            eFType = OFTReal;
        else if( poProperty->GetType() == GMLPT_StringList )
            eFType = OFTStringList;
        else if( poProperty->GetType() == GMLPT_IntegerList )
            eFType = OFTIntegerList;
        else if( poProperty->GetType() == GMLPT_RealList )
            eFType = OFTRealList;
        else
            eFType = OFTString;

        OGRFieldDefn oField( poProperty->GetName(), eFType );
        if ( EQUALN(oField.GetNameRef(), "ogr:", 4) )
          oField.SetName(poProperty->GetName()+4);
        if( poProperty->GetWidth() > 0 )
            oField.SetWidth( poProperty->GetWidth() );

        poLayer->GetLayerDefn()->AddFieldDefn( &oField );
    }

    return poLayer;
}
