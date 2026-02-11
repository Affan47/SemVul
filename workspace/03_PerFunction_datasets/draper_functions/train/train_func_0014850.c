Create(wxView* newview, wxFrame* parent, wxWindowID id, const wxString& title, const wxPoint& pos,
    const wxSize& size, long style, const wxString& name)
{
    if(!wxFrame::Create(parent, id, title, pos, size, style, name))
        return false;
    view = newview;
    if(view != NULL) {
        mgr = view->GetDocumentManager();
        view->SetFrame(this);
    }
    return true;
}
