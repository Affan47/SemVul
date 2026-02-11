AskForPathName()

{
    wxString newPathName = wxEmptyString;


    wxDirDialog dlg(::wxGetTopLevelParent(0),
                 _T("Select path "),
                 ::wxGetCwd(),
                 wxDD_DEFAULT_STYLE );


    wxPoint mousePosn = ::wxGetMousePosition();
    (&dlg)->Move(mousePosn.x, mousePosn.y);

    if (dlg.ShowModal() != wxID_OK) return wxEmptyString;
    return newPathName = dlg.GetPath();
}
