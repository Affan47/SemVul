ProcessEvent(wxEvent& event) {
    if(view != NULL) {
        view->Activate(true);
        if(view->ProcessEvent(event))
            return true;
    }
    if(mgr != NULL && mgr->ProcessEvent(event))
        return true;
    return wxFrame::ProcessEvent(event);
}
