FindBareXMLChild( const CPLXMLNode *psParent,
                                           const char *pszBareName )

{
    const CPLXMLNode *psCandidate = psParent->psChild;

    while( psCandidate != NULL )
    {
        if( psCandidate->eType == CXT_Element
            && EQUAL(BareGMLElement(psCandidate->pszValue), pszBareName) )
            return psCandidate;

        psCandidate = psCandidate->psNext;
    }

    return NULL;
}
