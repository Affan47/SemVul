FindElementByID( CPLXMLNode * psRoot,
                                    const char *pszID )

{
    if( psRoot == NULL )
        return NULL;

    CPLXMLNode *psSibling, *psReturn = NULL;


    for( psSibling = psRoot; psSibling != NULL; psSibling = psSibling->psNext)
    {
        if( psSibling->eType == CXT_Element )
        {

            const char* pszIDOfSibling = GetID( psSibling );
            if( pszIDOfSibling != NULL && EQUAL( pszIDOfSibling, pszID) )
                return psSibling;
        }
    }


    for( psSibling = psRoot; psSibling != NULL; psSibling = psSibling->psNext)
    {
        if( psSibling->eType == CXT_Element )
        {
            psReturn = FindElementByID( psSibling->psChild, pszID );
            if( psReturn != NULL )
                return psReturn;
        }
    }
    return NULL;
}
