endElementCityGMLGenericAttr()

{
    if( m_pszCityGMLGenericAttrName != NULL && m_bInCurField )
    {
        if( m_pszCurField != NULL )
        {
            m_poReader->SetFeaturePropertyDirectly( m_pszCityGMLGenericAttrName,
                                            m_pszCurField, -1 );
        }
        m_pszCurField = NULL;
        m_nCurFieldLen = m_nCurFieldAlloc = 0;
        m_bInCurField = FALSE;
        CPLFree(m_pszCityGMLGenericAttrName);
        m_pszCityGMLGenericAttrName = NULL;
    }

    if( m_inCityGMLGenericAttrDepth == m_nDepth )
    {
        POP_STATE();
    }

    return OGRERR_NONE;
}
