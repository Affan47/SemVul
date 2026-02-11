OnSuspendResumeGPU(wxCommandEvent& WXUNUSED(event)) {
    wxLogTrace(wxT("Function Start/End"), wxT("CTaskBarIcon::OnSuspendResumeGPU - Function Begin"));
    CMainDocument* pDoc      = wxGetApp().GetDocument();
    CC_STATUS      status;
    wxASSERT(pDoc);
    wxASSERT(wxDynamicCast(pDoc, CMainDocument));

    ResetTaskBar();
    pDoc->GetCoreClientStatus(status);
    if (status.gpu_mode_perm == RUN_MODE_NEVER) {
        pDoc->SetGPURunMode(RUN_MODE_RESTORE, 0);
    } else if (status.gpu_mode_perm != status.gpu_mode) {
        pDoc->SetGPURunMode(RUN_MODE_RESTORE, 0);
    } else {
        pDoc->SetGPURunMode(RUN_MODE_NEVER, 3600);
    }
    wxLogTrace(wxT("Function Start/End"), wxT("CTaskBarIcon::OnSuspendResumeGPU - Function End"));
}
