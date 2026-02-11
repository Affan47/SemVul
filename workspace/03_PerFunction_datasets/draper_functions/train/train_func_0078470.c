Close()
{

    if ( m_poDefn != NULL && m_bHeaderWrote == FALSE
         && m_eAccessMode != TABRead )
    {
        WriteMIFHeader();
    }

    if (m_poMIDFile)
    {
        m_poMIDFile->Close();
        delete m_poMIDFile;
        m_poMIDFile = NULL;
    }

    if (m_poMIFFile)
    {
        m_poMIFFile->Close();
        delete m_poMIFFile;
        m_poMIFFile = NULL;
    }

    if (m_poCurFeature)
    {
        delete m_poCurFeature;
        m_poCurFeature = NULL;
    }


    if (m_poDefn && m_poDefn->Dereference() == 0)
        delete m_poDefn;
    m_poDefn = NULL;

    if (m_poSpatialRef && m_poSpatialRef->Dereference() == 0)
        delete m_poSpatialRef;
    m_poSpatialRef = NULL;

    CPLFree(m_pszCoordSys);
    m_pszCoordSys = NULL;

    CPLFree(m_pszDelimiter);
    m_pszDelimiter = NULL;

    CPLFree(m_pszFname);
    m_pszFname = NULL;

    m_nVersion = 0;

    CPLFree(m_pszCharset);
    m_pszCharset = NULL;

    CPLFree(m_pabFieldIndexed);
    m_pabFieldIndexed = NULL;
    CPLFree(m_pabFieldUnique);
    m_pabFieldUnique = NULL;

    CPLFree( m_pszIndex );
    m_pszIndex = NULL;

    CPLFree(m_paeFieldType);
    m_paeFieldType = NULL;

    m_nCurFeatureId = 0;
    m_nPreloadedId = 0;
    m_nFeatureCount =0;

    m_bBoundsSet = FALSE;

    return 0;
}
