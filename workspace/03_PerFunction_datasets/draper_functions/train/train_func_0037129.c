initialize_daemon_at (const gchar *directory)
{
	gchar **ourenv, **daemonenv, **e;


	ourenv = gkd_util_build_environment (GKD_UTIL_IN_ENVIRONMENT);
	daemonenv = gkd_control_initialize (directory, run_components,
	                                    (const gchar**)ourenv);
	g_strfreev (ourenv);


	if (!daemonenv)
		return FALSE;


	for (e = daemonenv; *e; ++e)
		gkd_util_push_environment_full (*e);
	g_strfreev (daemonenv);

	return TRUE;
}
