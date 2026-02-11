CPLExtractSubSchema(CPLXMLNode* psSubXML, CPLXMLNode* psMainSchema)
{
    if (psSubXML->eType == CXT_Element && strcmp(psSubXML->pszValue, "?xml") == 0)
    {
        CPLXMLNode* psNext = psSubXML->psNext;
        psSubXML->psNext = NULL;
        CPLDestroyXMLNode(psSubXML);
        psSubXML = psNext;
    }

    if (psSubXML != NULL && psSubXML->eType == CXT_Comment)
    {
        CPLXMLNode* psNext = psSubXML->psNext;
        psSubXML->psNext = NULL;
        CPLDestroyXMLNode(psSubXML);
        psSubXML = psNext;
    }

    if (psSubXML != NULL && psSubXML->eType == CXT_Element &&
        (strcmp(psSubXML->pszValue, "schema") == 0 ||
         strcmp(psSubXML->pszValue, "xs:schema") == 0 ||
         strcmp(psSubXML->pszValue, "xsd:schema") == 0) &&
        psSubXML->psNext == NULL)
    {
        CPLXMLNode* psNext = psSubXML->psChild;
        while(psNext != NULL && psNext->eType != CXT_Element &&
              psNext->psNext != NULL && psNext->psNext->eType != CXT_Element)
        {

            if (psNext->eType == CXT_Attribute &&
                strncmp(psNext->pszValue, "xmlns:", 6) == 0 &&
                CPLGetXMLValue(psMainSchema, psNext->pszValue, NULL) == NULL)
            {
                CPLXMLNode* psAttr = CPLCreateXMLNode(NULL, CXT_Attribute, psNext->pszValue);
                CPLCreateXMLNode(psAttr, CXT_Text, psNext->psChild->pszValue);

                psAttr->psNext = psMainSchema->psChild;
                psMainSchema->psChild = psAttr;
            }
            psNext = psNext->psNext;
        }

        if (psNext != NULL && psNext->eType != CXT_Element &&
            psNext->psNext != NULL && psNext->psNext->eType == CXT_Element)
        {
            CPLXMLNode* psNext2 = psNext->psNext;
            psNext->psNext = NULL;
            CPLDestroyXMLNode(psSubXML);
            psSubXML = psNext2;
        }
    }

    return psSubXML;
}
