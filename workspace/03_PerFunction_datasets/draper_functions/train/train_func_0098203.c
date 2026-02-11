modperl_sys_term(void *data)
{

#if MP_PERL_VERSION_AT_LEAST(5, 9, 5) && defined(USE_ITHREADS)
    modperl_cleanup_data_t *cdata = (modperl_cleanup_data_t *)data;
    PERL_UNUSED_DECL PerlInterpreter *my_perl = cdata == NULL ? NULL : (PerlInterpreter *)cdata->data;
#endif
    MP_init_status = 0;
    MP_threads_started = 0;
    MP_post_post_config_phase = 0;

    MP_PERL_FREE_THREAD_KEY_WORKAROUND;

    MP_TRACE_i(MP_FUNC, "mod_perl sys term");

    modperl_env_unload();

    modperl_perl_pp_unset_all();

    PERL_SYS_TERM();

    return APR_SUCCESS;
}
