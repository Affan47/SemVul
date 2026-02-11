DisplayIdleState() {
    CMainDocument*      pDoc = wxGetApp().GetDocument();
    wxASSERT(pDoc);

    if ( pDoc->IsReconnecting() ) {
        error_time = 0;
        UpdateStaticText(&m_StatusValueText, _("Retrieving current status."));
    } else if ( pDoc->IsConnected() && pDoc->state.projects.size() == 0) {
        error_time = 0;
        UpdateStaticText(&m_StatusValueText, m_sNoProjectsString);
    } else if ( DownloadingResults() ) {
        error_time = 0;
        UpdateStaticText(&m_StatusValueText, _("Downloading work from the server."));
    } else if ( Suspended() ) {
        CC_STATUS status;
        pDoc->GetCoreClientStatus(status);
        if ( status.task_suspend_reason & SUSPEND_REASON_BATTERIES ) {
            UpdateStaticText(&m_StatusValueText, _("Processing Suspended:  Running On Batteries."));
        } else if ( status.task_suspend_reason & SUSPEND_REASON_USER_ACTIVE ) {
            UpdateStaticText(&m_StatusValueText, _("Processing Suspended:  User Active."));
        } else if ( status.task_suspend_reason & SUSPEND_REASON_USER_REQ ) {
            UpdateStaticText(&m_StatusValueText, _("Processing Suspended:  User paused processing."));
        } else if ( status.task_suspend_reason & SUSPEND_REASON_TIME_OF_DAY ) {
            UpdateStaticText(&m_StatusValueText, _("Processing Suspended:  Time of Day."));
        } else if ( status.task_suspend_reason & SUSPEND_REASON_BENCHMARKS ) {
            UpdateStaticText(&m_StatusValueText, _("Processing Suspended:  Benchmarks Running."));
        } else {
            UpdateStaticText(&m_StatusValueText, _("Processing Suspended."));
        }
    } else if ( ProjectUpdateScheduled() ) {
        error_time = 0;
        UpdateStaticText(&m_StatusValueText, _("Waiting to contact project servers."));
    } else {
        if ( error_time == 0 ) {
            error_time = time(NULL) + 10;
            UpdateStaticText(&m_StatusValueText, _("Retrieving current status"));
        } else if ( error_time < time(NULL) ) {

            if ( pDoc->IsConnected() ) {
                UpdateStaticText(&m_StatusValueText, _("No work available to process"));
            } else {
                UpdateStaticText(&m_StatusValueText, _("Unable to connect to the core client"));
            }
        } else {
            UpdateStaticText(&m_StatusValueText, _("Retrieving current status"));
        }
    }
}
