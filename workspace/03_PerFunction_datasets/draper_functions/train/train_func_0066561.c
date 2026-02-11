IsStandardButton(wxDialogHelper* dialog, wxButton* button)
{
    wxWindowID id = button->GetId();

    return (id == wxID_OK || id == wxID_CANCEL || id == wxID_YES || id == wxID_NO || id == wxID_SAVE ||
            id == wxID_APPLY || id == wxID_HELP || id == wxID_CONTEXT_HELP || dialog->IsUserButtonId(id));
}
