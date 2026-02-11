GetSkinsLocation() {

    wxString strSkinLocation = wxEmptyString;

#ifdef __WXMSW__
    strSkinLocation  = wxGetApp().GetRootDirectory();
    strSkinLocation += wxFileName::GetPathSeparator();
    strSkinLocation += wxT("skins");
#else
    strSkinLocation = wxString(wxGetCwd() + wxString(wxFileName::GetPathSeparator()) + wxT("skins"));
#endif

    return strSkinLocation;
}
