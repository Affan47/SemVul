SetupParser()

{
    if (fpGML == NULL)
        fpGML = VSIFOpenL(m_pszFilename, "rt");
    if (fpGML != NULL)
        VSIFSeekL( fpGML, 0, SEEK_SET );

    int bRet = -1;
#ifdef HAVE_EXPAT
    if (bUseExpatReader)
        bRet = SetupParserExpat();
#endif

#ifdef HAVE_XERCES
    if (!bUseExpatReader)
        bRet = SetupParserXerces();
#endif
    if (bRet < 0)
    {
        CPLError(CE_Failure, CPLE_AppDefined, "SetupParser(): shouldn't happen");
        return FALSE;
    }

    if (!bRet)
        return FALSE;

    m_bReadStarted = FALSE;


    PushState( m_poRecycledState ? m_poRecycledState : new GMLReadState() );
    m_poRecycledState = NULL;

    return TRUE;
}
