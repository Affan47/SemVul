SetImportLibraryFilename(const wxString& filename)
{
    if (filename.IsEmpty())
    {
        m_ImportLibraryFilename = _T("$(TARGET_OUTPUT_DIR)$(TARGET_OUTPUT_BASENAME)");
        SetModified(true);
        return;
    }
    else if (m_ImportLibraryFilename == filename)
        return;
    m_ImportLibraryFilename = UnixFilename(filename);
}
