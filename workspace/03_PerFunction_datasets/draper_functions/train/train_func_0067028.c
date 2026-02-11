AddAttributes(CPLXMLNode* psNode, void* attr)
{
    const Attributes* attrs = (const Attributes*) attr;

    CPLXMLNode* psLastChild = NULL;

    for(unsigned int i=0; i < attrs->getLength(); i++)
    {
        char* pszName = tr_strdup(attrs->getQName(i));
        char* pszValue = tr_strdup(attrs->getValue(i));

        CPLXMLNode* psChild = CPLCreateXMLNode(NULL, CXT_Attribute, pszName);
        CPLCreateXMLNode(psChild, CXT_Text, pszValue);

        CPLFree(pszName);
        CPLFree(pszValue);

        if (psLastChild == NULL)
            psNode->psChild = psChild;
        else
            psLastChild->psNext = psChild;
        psLastChild = psChild;
    }

    return psLastChild;
}
