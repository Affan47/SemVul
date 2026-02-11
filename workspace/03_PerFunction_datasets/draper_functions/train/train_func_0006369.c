ResetReading()

{
    const char *pszLine;

    m_poMIFFile->Rewind();

    while ((pszLine = m_poMIFFile->GetLine()) != NULL)
      if (EQUALN(pszLine,"DATA",4))
        break;

    while ((pszLine = m_poMIFFile->GetLine()) != NULL)
    {
        if (m_poMIFFile->IsValidFeature(pszLine))
          break;
    }

    m_poMIDFile->Rewind();
    m_poMIDFile->GetLine();


    if (m_poCurFeature)
    {
        delete m_poCurFeature;
        m_poCurFeature = NULL;
    }

    m_nCurFeatureId = 0;
    m_nPreloadedId = 1;
}
