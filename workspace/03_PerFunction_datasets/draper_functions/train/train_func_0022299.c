ap_process_resource_config(server_rec *s,
                                                    const char *fname,
                                                    ap_directive_t **conftree,
                                                    apr_pool_t *p,
                                                    apr_pool_t *ptemp)
{
    ap_configfile_t *cfp;
    cmd_parms parms;
    apr_status_t rv;
    const char *error;

    parms = default_parms;
    parms.pool = p;
    parms.temp_pool = ptemp;
    parms.server = s;
    parms.override = (RSRC_CONF | OR_ALL) & ~(OR_AUTHCFG | OR_LIMIT);
    parms.override_opts = OPT_ALL | OPT_SYM_OWNER | OPT_MULTI;

    rv = ap_pcfg_openfile(&cfp, p, fname);
    if (rv != APR_SUCCESS) {
        return apr_psprintf(p, "Could not open configuration file %s: %pm",
                            fname, &rv);
    }

    parms.config_file = cfp;
    error = ap_build_config(&parms, p, ptemp, conftree);
    ap_cfg_closefile(cfp);

    if (error) {
        if (parms.err_directive)
            return apr_psprintf(p, "Syntax error on line %d of %s: %s",
                                parms.err_directive->line_num,
                                parms.err_directive->filename, error);
        else
            return error;
    }

    return NULL;
}
