EstablishLayer( const char * pszLayerName,
                                    OGRwkbGeometryType eGeomType,
                                    NTFFeatureTranslator pfnTranslator,
                                    int nLeadRecordType,
                                    NTFGenericClass *poClass,
                                    ... )

{
    va_list     hVaArgs;
    OGRFeatureDefn *poDefn;
    OGRNTFLayer         *poLayer;


    poLayer = poDS->GetNamedLayer(pszLayerName);


    if( poLayer == NULL )
    {


        poDefn = new OGRFeatureDefn( pszLayerName );
        poDefn->SetGeomType( eGeomType );
        poDefn->Reference();


        va_start(hVaArgs, poClass);
        while( TRUE )
        {
            const char  *pszFieldName = va_arg(hVaArgs, const char *);
            OGRFieldType     eType;
            int          nWidth, nPrecision;

            if( pszFieldName == NULL )
                break;

            eType = (OGRFieldType) va_arg(hVaArgs, int);
            nWidth = va_arg(hVaArgs, int);
            nPrecision = va_arg(hVaArgs, int);

            OGRFieldDefn         oFieldDefn( pszFieldName, eType );
            oFieldDefn.SetWidth( nWidth );
            oFieldDefn.SetPrecision( nPrecision );

            poDefn->AddFieldDefn( &oFieldDefn );
        }

        va_end(hVaArgs);


        if( poClass != NULL )
        {
            for( int iGAtt = 0; iGAtt < poClass->nAttrCount; iGAtt++ )
            {
                const char      *pszFormat = poClass->papszAttrFormats[iGAtt];
                OGRFieldDefn    oFieldDefn( poClass->papszAttrNames[iGAtt],
                                            OFTInteger );

                if( EQUALN(pszFormat,"I",1) )
                {
                    oFieldDefn.SetType( OFTInteger );
                    oFieldDefn.SetWidth( poClass->panAttrMaxWidth[iGAtt] );
                }
                else if( EQUALN(pszFormat,"D",1)
                         || EQUALN(pszFormat,"A",1) )
                {
                    oFieldDefn.SetType( OFTString );
                    oFieldDefn.SetWidth( poClass->panAttrMaxWidth[iGAtt] );
                }
                else if( EQUALN(pszFormat,"R",1) )
                {
                    oFieldDefn.SetType( OFTReal );
                    oFieldDefn.SetWidth( poClass->panAttrMaxWidth[iGAtt]+1 );
                    if( pszFormat[2] == ',' )
                        oFieldDefn.SetPrecision(atoi(pszFormat+3));
                    else if( pszFormat[3] == ',' )
                        oFieldDefn.SetPrecision(atoi(pszFormat+4));
                }

                poDefn->AddFieldDefn( &oFieldDefn );


                if( poClass->pabAttrMultiple[iGAtt] )
                {
                    char szName[128];

                    sprintf( szName, "%s_LIST",
                             poClass->papszAttrNames[iGAtt] );

                    OGRFieldDefn oFieldDefnL( szName, OFTString );

                    poDefn->AddFieldDefn( &oFieldDefnL );
                }
            }
        }


        OGRFieldDefn     oTileID( "TILE_REF", OFTString );

        oTileID.SetWidth( 10 );

        poDefn->AddFieldDefn( &oTileID );


        poLayer = new OGRNTFLayer( poDS, poDefn, pfnTranslator );

        poDS->AddLayer( poLayer );
    }


    apoTypeTranslation[nLeadRecordType] = poLayer;
}
