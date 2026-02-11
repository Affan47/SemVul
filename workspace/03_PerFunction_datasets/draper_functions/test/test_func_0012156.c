GetStatusBar()
{
    wxWindow* topWnd = ::wxGetTopLevelParent(this);
    if ( topWnd && topWnd->IsKindOf(CLASSINFO(wxFrame)) )
    {
        wxFrame* pFrame = wxStaticCast(topWnd, wxFrame);
        if ( pFrame )
            return pFrame->GetStatusBar();
    }
    return NULL;
}
