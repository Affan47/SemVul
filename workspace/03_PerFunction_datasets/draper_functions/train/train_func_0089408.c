OnTaskAbort(wxCommandEvent& WXUNUSED(event)) {
    wxInt32  iAnswer        = 0;
    wxString strMessage     = wxEmptyString;
    CMainDocument* pDoc     = wxGetApp().GetDocument();

    wxASSERT(pDoc);
    wxASSERT(wxDynamicCast(pDoc, CMainDocument));

    if (!pDoc->IsUserAuthorized())
        return;

    TaskSelectionData* selData = ((CSimpleTaskPanel*)GetParent())->GetTaskSelectionData();
    if (selData == NULL) return;

    RESULT* result = lookup_result(selData->project_url, selData->result_name);
    if (result) {
#if SELECTBYRESULTNAME
        wxString name = wxString(selData->result_name, wxConvUTF8, strlen(selData->result_name));
#else
        wxString name = ((CSimpleTaskPanel*)GetParent())->GetSelectedTaskString();
#endif
        strMessage.Printf(
           _("Are you sure you want to abort this task '%s'?\n(Progress: %.1lf%%, Status: %s)"),
           name.c_str(), result->fraction_done * 100.0, result_description(result, false).c_str());

        iAnswer = wxGetApp().SafeMessageBox(
            strMessage,
            _("Abort task"),
            wxYES_NO | wxICON_QUESTION,
            this
        );

        if (wxYES != iAnswer) {
            return;
        }

        pDoc->WorkAbort(result->project_url, result->name);
    }
}
