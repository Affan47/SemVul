TestCapability( const char * pszCap )

{
    if (EQUAL(pszCap,OLCFastFeatureCount) &&
        m_poFilterGeom == NULL && m_poAttrQuery == NULL)
        return TRUE;
    else if (EQUAL(pszCap,OLCRandomRead))
        return TRUE;
    else if (EQUAL(pszCap,OLCFastSetNextByIndex) &&
             m_poFilterGeom == NULL && m_poAttrQuery == NULL)
        return TRUE;

    return FALSE;
}
