modperl_config_apply_PerlPostConfigRequire(server_rec *s,
                                               modperl_config_srv_t *scfg,
                                               apr_pool_t *p)
{
    modperl_require_file_t **requires;
    int i;
    MP_PERL_CONTEXT_DECLARE;

    requires = (modperl_require_file_t **)scfg->PerlPostConfigRequire->elts;
    for (i = 0; i < scfg->PerlPostConfigRequire->nelts; i++){
        int retval;

        MP_PERL_CONTEXT_STORE_OVERRIDE(scfg->mip->parent->perl);
        retval = modperl_require_file(aTHX_ requires[i]->file, TRUE);
        modperl_env_sync_srv_env_hash2table(aTHX_ p, scfg);
        modperl_env_sync_dir_env_hash2table(aTHX_ p, requires[i]->dcfg);
        MP_PERL_CONTEXT_RESTORE;

        if (retval) {
            MP_TRACE_d(MP_FUNC, "loaded Perl file: %s for server %s",
                       requires[i]->file, modperl_server_desc(s, p));
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                         "Can't load Perl file: %s for server %s, exiting...",
                         requires[i]->file, modperl_server_desc(s, p));

            return FALSE;
        }
    }

    return TRUE;
}
