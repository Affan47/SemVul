GMLParseFeatureType(CPLXMLNode *psSchemaNode,
                                const char* pszName,
                                const char *pszType)
{
    CPLXMLNode *psThis;
    for( psThis = psSchemaNode->psChild;
         psThis != NULL; psThis = psThis->psNext )
    {
        if( psThis->eType == CXT_Element
           && EQUAL(psThis->pszValue,"complexType")
           && EQUAL(CPLGetXMLValue(psThis,"name",""),pszType) )
        {
            break;
        }
    }
    if (psThis == NULL)
        return NULL;

    return GMLParseFeatureType(psSchemaNode, pszName, psThis);
}
