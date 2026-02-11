OnQuit(wxCommandEvent &event)

{

    if (m_bOnActivateBusy)
        return;
    wxCloseEvent evtClose;
    OnClose(evtClose);
}
