IsSuffixOfPath(wxFileName const & suffix, wxFileName const & path)
{
    if (path.GetFullName() != suffix.GetFullName())
    {
        return false;
    }

    wxArrayString suffixDirArray = suffix.GetDirs();
    wxArrayString pathDirArray = path.GetDirs();

    int j = pathDirArray.GetCount() - 1;
    for (int i = suffixDirArray.GetCount() - 1; i >= 0; i--)
    {

        if (suffixDirArray[i] == _T(".") || suffixDirArray[i] == _T(""))
            continue;


        if (j < 0)
            return false;


        if (suffixDirArray[i] == _T(".."))
            return true;

        else if (suffixDirArray[i] != pathDirArray[j])
            return false;

        j--;
    }

    if (suffix.IsAbsolute() && (j >= 0 || suffix.GetVolume() != path.GetVolume()))
        return false;


    return true;
}
