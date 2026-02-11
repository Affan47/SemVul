DetectIfGetFeatureSupportHits(CPLXMLNode* psRoot)
{
    CPLXMLNode* psOperationsMetadata =
        CPLGetXMLNode(psRoot, "OperationsMetadata");
    if (!psOperationsMetadata)
    {
        CPLDebug("WFS", "Could not find <OperationsMetadata>");
        return FALSE;
    }

    CPLXMLNode* psChild = psOperationsMetadata->psChild;
    while(psChild)
    {
        if (psChild->eType == CXT_Element &&
            strcmp(psChild->pszValue, "Operation") == 0 &&
            strcmp(CPLGetXMLValue(psChild, "name", ""), "GetFeature") == 0)
        {
            break;
        }
        psChild = psChild->psNext;
    }
    if (!psChild)
    {
        CPLDebug("WFS", "Could not find <Operation name=\"GetFeature\">");
        return FALSE;
    }

    psChild = psChild->psChild;
    while(psChild)
    {
        if (psChild->eType == CXT_Element &&
            strcmp(psChild->pszValue, "Parameter") == 0 &&
            strcmp(CPLGetXMLValue(psChild, "name", ""), "resultType") == 0)
        {
            break;
        }
        psChild = psChild->psNext;
    }
   if (!psChild)
    {
        CPLDebug("WFS", "Could not find <Parameter name=\"resultType\">");
        return FALSE;
    }

    psChild = psChild->psChild;
    while(psChild)
    {
        if (psChild->eType == CXT_Element &&
            strcmp(psChild->pszValue, "Value") == 0)
        {
            CPLXMLNode* psChild2 = psChild->psChild;
            while(psChild2)
            {
                if (psChild2->eType == CXT_Text &&
                    strcmp(psChild2->pszValue, "hits") == 0)
                {
                    CPLDebug("WFS", "GetFeature operation supports hits");
                    return TRUE;
                }
                psChild2 = psChild2->psNext;
            }
        }
        psChild = psChild->psNext;
    }

    return FALSE;
}
