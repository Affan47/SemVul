CreateFeature( OGRFeature *poFeature )

{
    if( !bUpdate )
    {
        CPLError( CE_Failure, CPLE_NoWriteAccess,
                  "Can't create features on read-only dataset." );
        return OGRERR_FAILURE;
    }


    if( !bHeaderComplete )
    {
        OGRErr eErr = CompleteHeader( poFeature->GetGeometryRef() );

        if( eErr != OGRERR_NONE )
            return eErr;
    }


    OGRGeometry *poGeom = poFeature->GetGeometryRef();

    if( poGeom == NULL )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "Features without geometry not supported by GMT writer." );
        return OGRERR_FAILURE;
    }

    if( poFeatureDefn->GetGeomType() == wkbUnknown )
        poFeatureDefn->SetGeomType(wkbFlatten(poGeom->getGeometryType()));


    if( poFeatureDefn->GetGeomType() != wkbPoint )
        VSIFPrintfL( fp, ">\n" );


    if( poFeatureDefn->GetFieldCount() > 0 )
    {
        int iField;
        CPLString osFieldData;

        for( iField = 0; iField < poFeatureDefn->GetFieldCount(); iField++ )
        {
            OGRFieldType eFType=poFeatureDefn->GetFieldDefn(iField)->GetType();
            const char *pszRawValue = poFeature->GetFieldAsString(iField);
            char *pszEscapedVal;

            if( iField > 0 )
                osFieldData += "|";


            if( eFType == OFTInteger || eFType == OFTReal )
                while( *pszRawValue == ' ' )
                    pszRawValue++;

            if( strchr(pszRawValue,' ') || strchr(pszRawValue,'|')
                || strchr(pszRawValue, '\t') || strchr(pszRawValue, '\n') )
            {
                pszEscapedVal =
                    CPLEscapeString( pszRawValue,
                                     -1, CPLES_BackslashQuotable );

                osFieldData += "\"";
                osFieldData += pszEscapedVal;
                osFieldData += "\"";
                CPLFree( pszEscapedVal );
            }
            else
                osFieldData += pszRawValue;
        }

        VSIFPrintfL( fp, "# @D%s\n", osFieldData.c_str() );
    }


    return WriteGeometry( (OGRGeometryH) poGeom, TRUE );
}
