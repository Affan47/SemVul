immunix_cmd_ch_path(cmd_parms *cmd, void *mconfig, const char *parm1)
{
    if (path_warn_once == 0) {
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, "ImmHatName is "
                     "deprecated, please use AAHatName instead");
        path_warn_once = 1;
    }
    return aa_cmd_ch_path(cmd, mconfig, parm1);
}
