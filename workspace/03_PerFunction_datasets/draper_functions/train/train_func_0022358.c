GetDocTotalCredit(wxInt32 item, float& fBuffer) const {
    PROJECT* project = NULL;
    CMainDocument* pDoc = wxGetApp().GetDocument();

    if (pDoc) {
        project = pDoc->project(item);
    }

    if (project) {
        fBuffer = project->user_total_credit;
    } else {
        fBuffer = 0.0;
    }
}
