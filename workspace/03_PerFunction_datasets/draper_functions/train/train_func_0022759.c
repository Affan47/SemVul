retrocl_init_trimming (void)
{
    const char *cl_maxage;
    time_t ageval;

    cl_maxage = retrocl_get_config_str(CONFIG_CHANGELOG_MAXAGE_ATTRIBUTE);

    if (cl_maxage == NULL) {
      LDAPDebug0Args(LDAP_DEBUG_TRACE,"No maxage, not trimming retro changelog.\n");
      return;
    }
    ageval = age_str2time (cl_maxage);
    slapi_ch_free ((void **)&cl_maxage);

    ts.ts_c_max_age = ageval;
    ts.ts_s_last_trim = (time_t) 0L;
    ts.ts_s_trimming = 0;
    if (( ts.ts_s_trim_mutex = PR_NewLock()) == NULL ) {
	slapi_log_error( SLAPI_LOG_FATAL, RETROCL_PLUGIN_NAME, "set_changelog_trim_constraints: "
		"cannot create new lock.\n" );
	exit( 1 );
    }
    ts.ts_s_initialized = 1;
    retrocl_trimming = 1;

    retrocl_trim_ctx = slapi_eq_repeat(retrocl_housekeeping,
                                       NULL, (time_t)0,

                                       CHANGELOGDB_TRIM_INTERVAL);

}
