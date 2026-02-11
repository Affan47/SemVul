GetSingleChildElement(CPLXMLNode* psNode, const char* pszExpectedValue)
{
    CPLXMLNode* psChild = NULL;
    CPLXMLNode* psIter;

    if( psNode == NULL )
        return NULL;

    psIter = psNode->psChild;
    if( psIter == NULL )
        return NULL;
    while( psIter != NULL )
    {
        if( psIter->eType == CXT_Element )
        {
            if( psChild != NULL )
                return NULL;
            if( pszExpectedValue != NULL &&
                strcmp(psIter->pszValue, pszExpectedValue) != 0 )
                return NULL;
            psChild = psIter;
        }
        psIter = psIter->psNext;
    }
    return psChild;
}
