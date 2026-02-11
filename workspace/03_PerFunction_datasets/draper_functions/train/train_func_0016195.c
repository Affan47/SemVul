InitializeIndexSupport( const char *pszFilename )

{
    OGRErr eErr;

    if (m_poAttrIndex != NULL)
        return OGRERR_NONE;

    m_poAttrIndex = OGRCreateDefaultLayerIndex();

    eErr = m_poAttrIndex->Initialize( pszFilename, this );
    if( eErr != OGRERR_NONE )
    {
        delete m_poAttrIndex;
        m_poAttrIndex = NULL;
    }

    return eErr;
}
