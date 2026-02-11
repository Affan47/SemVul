OnActivate(wxActivateEvent& event) {
    wxFrame::OnActivate(event);
    if(view != NULL)
        view->Activate(event.GetActive());
}
