NextFeatureXerces()

{
    GMLFeature *poReturn = NULL;

    if (m_bEOF)
        return NULL;

    try
    {
        if( !m_bReadStarted )
        {
            if( m_poSAXReader == NULL )
                SetupParser();

            m_bReadStarted = TRUE;

            if (m_GMLInputSource == NULL)
                return NULL;

            if( !m_poSAXReader->parseFirst( *m_GMLInputSource, m_oToFill ) )
                return NULL;
        }

        while( m_poCompleteFeature == NULL
               && !m_bStopParsing
               && m_poSAXReader->parseNext( m_oToFill ) ) {}

        if (m_poCompleteFeature == NULL)
            m_bEOF = TRUE;

        poReturn = m_poCompleteFeature;
        m_poCompleteFeature = NULL;

    }
    catch (const XMLException& toCatch)
    {
        char *pszErrorMessage = tr_strdup( toCatch.getMessage() );
        CPLDebug( "GML",
                  "Error during NextFeature()! Message:\n%s",
                  pszErrorMessage );
        CPLFree(pszErrorMessage);
        m_bStopParsing = TRUE;
    }
    catch (const SAXException& toCatch)
    {
        char *pszErrorMessage = tr_strdup( toCatch.getMessage() );
        CPLError(CE_Failure, CPLE_AppDefined, "%s", pszErrorMessage);
        CPLFree(pszErrorMessage);
        m_bStopParsing = TRUE;
    }

    return poReturn;
}
