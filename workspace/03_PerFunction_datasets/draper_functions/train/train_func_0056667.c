FindFirstFileInIncludeDirs(const wxString& file)
{
    wxString FirstFound = m_GlobalIncludes.GetItem(file);
    if (FirstFound.IsEmpty())
    {
        wxArrayString FoundSet = FindFileInIncludeDirs(file,true);
        if (FoundSet.GetCount())
        {
            FirstFound = UnixFilename(FoundSet[0]);
            m_GlobalIncludes.AddItem(file, FirstFound);
        }
    }
    return FirstFound;
}
