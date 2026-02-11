GetBasePath() const
{
    if (m_Filename.IsEmpty())
        return _T(".");

    wxFileName basePath(m_Filename);
    wxString base = basePath.GetPath(wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR);
    return !base.IsEmpty() ? base : _T(".");
}
