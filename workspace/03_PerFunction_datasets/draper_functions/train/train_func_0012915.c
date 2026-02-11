OnButtonClick(wxCommandEvent& event)
{
    switch (event.GetId())
    {
        case wxID_OK:
            EndModal(wxOK);
            break;
        case wxID_YES:
            EndModal(wxYES);
            break;
        case wxID_NO:
            EndModal(wxNO);
            break;
        case wxID_CANCEL:
            EndModal(wxCANCEL);
            break;
    }
}
