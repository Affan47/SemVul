session_connect(void)
{
    SmcCallbacks cb;
    gchar *oldid;
    gchar sm_err[SM_ERR_LEN];


    cb.save_yourself.callback = sm_save_yourself;
    cb.save_yourself.client_data = NULL;
    cb.die.callback = sm_die;
    cb.die.client_data = NULL;
    cb.save_complete.callback = sm_save_complete;
    cb.save_complete.client_data = NULL;
    cb.shutdown_cancelled.callback = sm_shutdown_cancelled;
    cb.shutdown_cancelled.client_data = NULL;


    oldid = ob_sm_id;
    ob_debug_type(OB_DEBUG_SM, "Connecting to SM with id: %s",
                  oldid ? oldid : "(null)");
    sm_conn = SmcOpenConnection(NULL, NULL, 1, 0,
                                SmcSaveYourselfProcMask |
                                SmcDieProcMask |
                                SmcSaveCompleteProcMask |
                                SmcShutdownCancelledProcMask,
                                &cb, oldid, &ob_sm_id,
                                SM_ERR_LEN-1, sm_err);
    g_free(oldid);
    ob_debug_type(OB_DEBUG_SM, "Connected to SM with id: %s", ob_sm_id);
    if (sm_conn == NULL)
        ob_debug("Failed to connect to session manager: %s", sm_err);
    return sm_conn != NULL;
}
