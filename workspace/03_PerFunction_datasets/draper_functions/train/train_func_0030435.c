PrescanForTemplate ()
{
    int iCount = 0;
    GMLFeature      *poFeature;

    GFSTemplateList *pCC = new GFSTemplateList();


    while( (poFeature = NextFeature()) != NULL )
    {
        GMLFeatureClass *poClass = poFeature->GetClass();
        const CPLXMLNode* const * papsGeomList = poFeature->GetGeometryList();
        int b_has_geom = FALSE;

        if( papsGeomList != NULL )
        {
            int i = 0;
            const CPLXMLNode *psNode = papsGeomList[i];
            while( psNode != NULL )
            {
                b_has_geom = TRUE;
                i++;
                psNode = papsGeomList[i];
            }
        }
        pCC->Update( poClass->GetElementName(), b_has_geom );

        delete poFeature;
    }

    gmlUpdateFeatureClasses( pCC, this, &m_bSequentialLayers );
    if ( m_bSequentialLayers == TRUE )
        ReArrangeTemplateClasses( pCC );
    iCount = pCC->GetClassCount();
    delete pCC;
    CleanupParser();
    return iCount > 0;
}
