GetFullFileName(const wxString& src, const wxString& tgt, bool isGlobal)
{
    wxString fullname;
    if (isGlobal)
    {
        fullname = FindFirstFileInIncludeDirs(tgt);
        if (fullname.IsEmpty())
        {


            wxString base = wxFileName(src).GetPath(wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR);
            fullname = FindFirstFileInIncludeDirs(base + tgt);
        }
    }


    else
    {
        wxFileName fname(tgt);
        wxFileName source(src);
        if (NormalizePath(fname,source.GetPath(wxPATH_GET_VOLUME)))
        {
            fullname = fname.GetFullPath();
            if (!wxFileExists(fullname))
                fullname.Clear();
        }
    }

    return fullname;
}
