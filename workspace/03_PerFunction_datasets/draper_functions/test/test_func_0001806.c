ReadFile()
{
    bool success = false;
    wxString fileName = wxEmptyString;
    if (m_Loader)
    {
        fileName    = m_Loader->FileName();
        char* data  = m_Loader->GetData();
        m_BufferLen = m_Loader->GetLength();


#if wxUSE_UNICODE
        m_Buffer = wxString(data, wxConvUTF8, m_BufferLen + 1);
        if (m_Buffer.Length() == 0)
        {

            m_Buffer = wxString(data, wxConvISO8859_1, m_BufferLen + 1);
        }
#else
        m_Buffer = wxString(data, m_BufferLen + 1);
#endif

        success = (data != 0);
    }
    else
    {
        if ( !wxFileExists(m_Filename) )
            return false;


        wxFile file(m_Filename);
        if ( !cbRead(file, m_Buffer) )
            return false;

        fileName = m_Filename;
        success  = true;
    }

    m_BufferLen = m_Buffer.Length();


    m_Buffer += _T(' ');

    return success;
}
