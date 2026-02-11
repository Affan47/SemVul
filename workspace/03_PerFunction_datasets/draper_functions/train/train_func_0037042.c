Close()
{

    if (m_eAccessMode == TABWrite && m_poRelation)
        WriteTABFile();

    for(int i=0; m_papoTABFiles && i<m_numTABFiles; i++)
    {
        if (m_papoTABFiles[i])
            delete m_papoTABFiles[i];
    }
    CPLFree(m_papoTABFiles);
    m_papoTABFiles = NULL;
    m_numTABFiles = 0;


    if (m_eAccessMode == TABWrite && m_pszFname)
    {
        m_pszFname[strlen(m_pszFname)-4] = '\0';
        char *pszFile = CPLStrdup(CPLSPrintf("%s2.map", m_pszFname));
        TABAdjustFilenameExtension(pszFile);
        VSIUnlink(pszFile);

        sprintf(pszFile, "%s2.id", m_pszFname);
        TABAdjustFilenameExtension(pszFile);
        VSIUnlink(pszFile);

        CPLFree(pszFile);
    }


    CPLFree(m_pszFname);
    m_pszFname = NULL;

    CSLDestroy(m_papszTABFile);
    m_papszTABFile = NULL;

    CPLFree(m_pszVersion);
    m_pszVersion = NULL;
    CPLFree(m_pszCharset);
    m_pszCharset = NULL;

    CSLDestroy(m_papszTABFnames);
    m_papszTABFnames = NULL;

    CSLDestroy(m_papszFieldNames);
    m_papszFieldNames = NULL;
    CSLDestroy(m_papszWhereClause);
    m_papszWhereClause = NULL;

    m_nMainTableIndex = -1;

    if (m_poRelation)
        delete m_poRelation;
    m_poRelation = NULL;

    m_bRelFieldsCreated = FALSE;

    return 0;
}
