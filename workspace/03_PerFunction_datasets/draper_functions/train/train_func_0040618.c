GetInsertionIndex(const wxString& filePath, long nbItemstoInsert )
{
    wxASSERT(nbItemstoInsert > 0);
    wxFileName fileName(filePath);
    wxString   string(filePath);
    long index = 0;

    if ( m_FileSorting == SortByFileName )
    {
        string = fileName.GetFullName();
    }
