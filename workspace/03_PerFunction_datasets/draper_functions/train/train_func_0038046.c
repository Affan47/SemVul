pam_passthru_preop_init(Slapi_PBlock *pb)
{
    int status = 0;
    if ( slapi_pblock_set( pb, SLAPI_PLUGIN_PRE_BIND_FN,
                           (void *)pam_passthru_bindpreop ) ||
         slapi_pblock_set( pb, SLAPI_PLUGIN_CLOSE_FN, (void *)pam_passthru_bindpreop_close )) {
        slapi_log_error( SLAPI_LOG_FATAL, PAM_PASSTHRU_PLUGIN_SUBSYSTEM,
                         "pam_passthruauth_preop_init failed\n");
        status = -1;
    }
    return status;
}
