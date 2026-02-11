gmlHugeFileCheckXrefs( struct huge_helper *helper,
                                   const CPLXMLNode *psNode )
{

    if( psNode->eType == CXT_Element )
    {
        if( EQUAL(psNode->pszValue, "Edge") == TRUE )
        {
            CPLString *gmlId = NULL;
            if( gmlHugeFindGmlId( psNode, &gmlId ) == TRUE )
            {
                char * gmlText = CPLSerializeXMLTree((CPLXMLNode *)psNode);
                CPLString *gmlValue = new CPLString(gmlText);
                CPLFree( gmlText );
                struct huge_tag *pItem = gmlHugeAddToHelper( helper, gmlId,
                                                             gmlValue );
                if( pItem != NULL )
                    gmlHugeFileNodeCoords( pItem, psNode, &(helper->nodeSrs) );
                else
                {
                    delete gmlId;
                    delete gmlValue;
                }
            }
        }
    }


    const CPLXMLNode *psChild = psNode->psChild;
    while( psChild != NULL )
    {
        if( psChild->eType == CXT_Element )
        {
            if( EQUAL(psChild->pszValue, "Edge") == TRUE ||
                EQUAL(psChild->pszValue, "directedEdge") == TRUE )
            {
                gmlHugeFileCheckXrefs( helper, psChild );
            }
            if( EQUAL(psChild->pszValue, "directedFace") == TRUE )
            {
                const CPLXMLNode *psFace = psChild->psChild;
                if( psFace != NULL )
                {
                    if( psFace->eType == CXT_Element &&
                        EQUAL(psFace->pszValue, "Face") == TRUE)
                    {
                        const CPLXMLNode *psDirEdge = psFace->psChild;
                        while (psDirEdge != NULL)
                        {
                            const CPLXMLNode *psEdge = psDirEdge->psChild;
                            while( psEdge != NULL)
                            {
                                if( psEdge->eType == CXT_Element &&
                                    EQUAL(psEdge->pszValue, "Edge") == TRUE)
                                    gmlHugeFileCheckXrefs( helper, psEdge );
                                psEdge = psEdge->psNext;
                            }
                            psDirEdge = psDirEdge->psNext;
                        }
                    }
                }
            }
        }
        psChild = psChild->psNext;
    }


    const CPLXMLNode *psNext = psNode->psNext;
    while( psNext != NULL )
    {
        if( psNext->eType == CXT_Element )
        {
            if( EQUAL(psNext->pszValue, "Edge") == TRUE ||
                EQUAL(psNext->pszValue, "directedEdge") == TRUE )
            {
                gmlHugeFileCheckXrefs( helper, psNext );
            }
        }
        psNext = psNext->psNext;
    }
}
