suphp_handle_cmd_remove_handler(cmd_parms *cmd,
                                                   void *mconfig,
                                                   const char *arg)
{
    suphp_conf *cfg;
    if (mconfig)
        cfg = (suphp_conf *) mconfig;
    else
        cfg = (suphp_conf *) ap_get_module_config(cmd->server->module_config, &suphp_module);


    apr_table_set(cfg->handlers, arg, "0");

    return NULL;
}
