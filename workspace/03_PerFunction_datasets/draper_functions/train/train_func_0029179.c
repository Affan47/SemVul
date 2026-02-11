makePathsRelativeIfNeeded(const wxArrayString& paths, const wxString& basePath)
{
    wxArrayString relatives = paths;
    for(std::size_t index = 0U; index < paths.Count(); ++index)
    {
        wxString& path = relatives[index];
        path = makePathRelativeIfNeeded(path, basePath);
    }
    return relatives;
}
