InitFilename(const wxString& filename)

{
    if (filename.IsEmpty())
        m_Filename = realpath(CreateUniqueFilename());
    else
        m_Filename = realpath(filename);

    wxFileName fname;
    fname.Assign(m_Filename);
    m_Shortname = fname.GetFullName();

}
