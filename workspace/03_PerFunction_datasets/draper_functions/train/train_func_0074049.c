OnAppActivated(CodeBlocksEvent& event)
{
    event.Skip();
    if (!platform::gtk)
        return;
    wxTextDataObject data;
    bool gotData = false;
    wxTheClipboard->UsePrimarySelection(true);
    if (wxTheClipboard->Open())
    {
        gotData = wxTheClipboard->GetData(data);
        wxTheClipboard->Close();
    }
    wxTheClipboard->UsePrimarySelection(false);
    if (gotData && !data.GetText().IsEmpty())
        m_pData->m_SelectionClipboard = data.GetText();
}
