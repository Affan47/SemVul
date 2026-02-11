GetINDFileRef()
{
    if (m_pszFname == NULL)
        return NULL;

    if (m_eAccessMode == TABRead && m_poINDFile == NULL)
    {


        m_poINDFile = new TABINDFile;

        if ( m_poINDFile->Open(m_pszFname, "r", TRUE) != 0)
        {

            delete m_poINDFile;
            m_poINDFile = NULL;
        }
        else if (m_panIndexNo && m_poDATFile)
        {


            for(int i=0; i<m_poDATFile->GetNumFields(); i++)
            {
                if (m_panIndexNo[i] > 0)
                {
                    m_poINDFile->SetIndexFieldType(m_panIndexNo[i],
                                                   GetNativeFieldType(i));
                }
            }
        }
    }

    return m_poINDFile;
}
