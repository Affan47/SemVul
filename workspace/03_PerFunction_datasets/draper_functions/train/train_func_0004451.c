CPLMoveImportAtBeginning(CPLXMLNode* psXML)
{
    CPLXMLNode* psIter;
    CPLXMLNode* psPrev;
    CPLXMLNode* psSchema;

    psSchema = CPLGetXMLNode(psXML, "=schema");
    if (psSchema == NULL)
        psSchema = CPLGetXMLNode(psXML, "=xs:schema");
    if (psSchema == NULL)
        psSchema = CPLGetXMLNode(psXML, "=xsd:schema");
    if (psSchema == NULL)
        return;

    psPrev = NULL;
    psIter = psSchema->psChild;
    while(psIter)
    {
        if (psPrev != NULL && psIter->eType == CXT_Element &&
            (strcmp(psIter->pszValue, "import") == 0 ||
             strcmp(psIter->pszValue, "xs:import") == 0 ||
             strcmp(psIter->pszValue, "xsd:import") == 0))
        {

            CPLXMLNode* psNext = psIter->psNext;

            psPrev->psNext = psNext;

            CPLXMLNode* psFirstChild = psSchema->psChild;
            psSchema->psChild = psIter;
            psIter->psNext = psFirstChild;

            psIter = psNext;
            continue;
        }

        psPrev = psIter;
        psIter = psIter->psNext;
    }
}
