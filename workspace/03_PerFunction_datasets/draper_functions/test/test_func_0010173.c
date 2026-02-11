makePathRelativeIfNeeded(const wxString& path, const wxString& basePath)
{
    wxString relative = path;
    wxFileName fname = path;
    if (fname.IsAbsolute())
    {
        fname.MakeRelativeTo(basePath);
        relative = fname.GetFullPath();
    }
    return relative;
}
