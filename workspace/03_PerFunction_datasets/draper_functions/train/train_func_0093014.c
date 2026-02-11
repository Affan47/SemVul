OnTaskShowGraphics(wxCommandEvent& WXUNUSED(event)) {
    CMainDocument* pDoc     = wxGetApp().GetDocument();

    wxASSERT(pDoc);
    wxASSERT(wxDynamicCast(pDoc, CMainDocument));

    TaskSelectionData* selData = ((CSimpleTaskPanel*)GetParent())->GetTaskSelectionData();
    if (selData == NULL) return;

    RESULT* result = lookup_result(selData->project_url, selData->result_name);
    if (result) {
        pDoc->WorkShowGraphics(result);
    }
}
