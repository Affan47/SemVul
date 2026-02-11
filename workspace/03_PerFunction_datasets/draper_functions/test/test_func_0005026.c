NITFCreateXMLTre(NITFFile* psFile,
                             const char* pszTREName,
                             const char *pachTRE,
                             int nTRESize)
{
    int nTreLength, nTreMinLength = -1, nTreMaxLength = -1;
    int bError = FALSE;
    int nTreOffset = 0;
    CPLXMLNode* psTreNode;
    CPLXMLNode* psOutXMLNode = NULL;
    int nMDSize = 0, nMDAlloc = 0;

    psTreNode = NITFFindTREXMLDescFromName(psFile, pszTREName);
    if (psTreNode == NULL)
    {
        if (!(EQUALN(pszTREName, "RPF", 3) || strcmp(pszTREName, "XXXXXX") == 0))
        {
            CPLDebug("NITF", "Cannot find definition of TRE %s in %s",
                    pszTREName, NITF_SPEC_FILE);
        }
        return NULL;
    }

    nTreLength = atoi(CPLGetXMLValue(psTreNode, "length", "-1"));
    nTreMinLength = atoi(CPLGetXMLValue(psTreNode, "minlength", "-1"));
    nTreMaxLength = atoi(CPLGetXMLValue(psTreNode, "maxlength", "-1"));

    if( (nTreLength > 0 && nTRESize != nTreLength) ||
        (nTreMinLength > 0 && nTRESize < nTreMinLength) )
    {
        CPLError( CE_Warning, CPLE_AppDefined,
                  "%s TRE wrong size, ignoring.", pszTREName );
        return NULL;
    }

    psOutXMLNode = CPLCreateXMLNode(NULL, CXT_Element, "tre");
    CPLCreateXMLNode(CPLCreateXMLNode(psOutXMLNode, CXT_Attribute, "name"),
                     CXT_Text, pszTREName);

    CSLDestroy(NITFGenericMetadataReadTREInternal(NULL,
                                                  &nMDSize,
                                                  &nMDAlloc,
                                                  psOutXMLNode,
                                                  pszTREName,
                                                  pachTRE,
                                                  nTRESize,
                                                  psTreNode,
                                                  &nTreOffset,
                                                  "",
                                                  &bError));

    if (bError == FALSE && nTreLength > 0 && nTreOffset != nTreLength)
    {
        CPLError( CE_Warning, CPLE_AppDefined,
                  "Inconsistent declaration of %s TRE",
                  pszTREName );
    }
    if (nTreOffset < nTRESize)
        CPLDebug("NITF", "%d remaining bytes at end of %s TRE",
                 nTRESize -nTreOffset, pszTREName);

    return psOutXMLNode;
}
