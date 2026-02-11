LoadFile(const wxString& fileName)
{
    if (!fileName.IsEmpty())
    {
        wxFFile file( fileName, _T("r") );
        if (file.IsOpened())
        {
            file.ReadAll(&m_text);
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}
