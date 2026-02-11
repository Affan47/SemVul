GetDocResourcePercent(wxInt32 item, float& fBuffer) const {
    PROJECT* project = NULL;
    CMainDocument* pDoc = wxGetApp().GetDocument();

    if (pDoc) {
        project = pDoc->project(item);
    }

    if (project && pDoc) {
        fBuffer = (project->resource_share / pDoc->m_fProjectTotalResourceShare) * 100;
    } else {
        fBuffer = 0.0;
    }
}
