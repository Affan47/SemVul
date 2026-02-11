GetNextUnfilteredFeature()

{
    OGRFeature *poFeature = NULL;


    if( !apoPendingFeatures.empty() )
    {
        poFeature = apoPendingFeatures.front();
        apoPendingFeatures.pop();

        poFeature->SetFID( iNextFID++ );
        return poFeature;
    }


    char szLineBuf[257];
    int nCode;

    while( poFeature == NULL )
    {

        while( (nCode = poDS->ReadValue(szLineBuf,sizeof(szLineBuf))) > 0 ) {}

        if( nCode == -1 )
        {
            CPLDebug( "DXF", "Unexpected end of data without ENDSEC." );
            return NULL;
        }

        if( EQUAL(szLineBuf,"ENDSEC") )
        {

            poDS->UnreadValue();
            return NULL;
        }

        if( EQUAL(szLineBuf,"ENDBLK") )
        {

            poDS->UnreadValue();
            return NULL;
        }


        oStyleProperties.clear();

        if( EQUAL(szLineBuf,"POINT") )
        {
            poFeature = TranslatePOINT();
        }
        else if( EQUAL(szLineBuf,"MTEXT") )
        {
            poFeature = TranslateMTEXT();
        }
        else if( EQUAL(szLineBuf,"TEXT")
                 || EQUAL(szLineBuf,"ATTDEF") )
        {
            poFeature = TranslateTEXT();
        }
        else if( EQUAL(szLineBuf,"LINE") )
        {
            poFeature = TranslateLINE();
        }
        else if( EQUAL(szLineBuf,"POLYLINE") )
        {
            poFeature = TranslatePOLYLINE();
        }
        else if( EQUAL(szLineBuf,"LWPOLYLINE") )
        {
            poFeature = TranslateLWPOLYLINE();
        }
        else if( EQUAL(szLineBuf,"CIRCLE") )
        {
            poFeature = TranslateCIRCLE();
        }
        else if( EQUAL(szLineBuf,"ELLIPSE") )
        {
            poFeature = TranslateELLIPSE();
        }
        else if( EQUAL(szLineBuf,"ARC") )
        {
            poFeature = TranslateARC();
        }
        else if( EQUAL(szLineBuf,"SPLINE") )
        {
            poFeature = TranslateSPLINE();
        }
        else if( EQUAL(szLineBuf,"INSERT") )
        {
            poFeature = TranslateINSERT();
        }
        else if( EQUAL(szLineBuf,"DIMENSION") )
        {
            poFeature = TranslateDIMENSION();
        }
        else if( EQUAL(szLineBuf,"HATCH") )
        {
            poFeature = TranslateHATCH();
        }
        else
        {
            if( oIgnoredEntities.count(szLineBuf) == 0 )
            {
                oIgnoredEntities.insert( szLineBuf );
                CPLDebug( "DWG", "Ignoring one or more of entity '%s'.",
                          szLineBuf );
            }
        }
    }


    poFeature->SetFID( iNextFID++ );
    m_nFeaturesRead++;

    return poFeature;
}
