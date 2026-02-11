DoSaveFile(const wxString& filename, int WXUNUSED(fileType))
{
#if wxUSE_FFILE || wxUSE_FILE

#if wxUSE_FFILE


    wxFFile file(filename, wxT("wb"));
#elif wxUSE_FILE
    wxFile file(filename, wxFile::write);
#endif

    if (file.IsOpened() && file.Write(GetValue(), *wxConvCurrent))
    {
        SetSavePoint();

        return true;
    }

#endif

    return false;
}
