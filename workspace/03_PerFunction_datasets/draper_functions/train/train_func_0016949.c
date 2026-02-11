run_script(const char *action)
{
	char *env_PREVIOUS, *env_CURRENT;
	char *argv[5];
	int r;

	bb_error_msg("executing '%s %s %s'", G.script_name, G.iface, action);

	argv[0] = (char*) G.script_name;
	argv[1] = (char*) G.iface;
	argv[2] = (char*) action;
	argv[3] = (char*) G.extra_arg;
	argv[4] = NULL;

	env_PREVIOUS = xasprintf("%s=%s", IFPLUGD_ENV_PREVIOUS, strstatus(G.iface_prev_status));
	putenv(env_PREVIOUS);
	env_CURRENT = xasprintf("%s=%s", IFPLUGD_ENV_CURRENT, strstatus(G.iface_last_status));
	putenv(env_CURRENT);


	r = spawn_and_wait(argv);

	unsetenv(IFPLUGD_ENV_PREVIOUS);
	unsetenv(IFPLUGD_ENV_CURRENT);
	free(env_PREVIOUS);
	free(env_CURRENT);

	bb_error_msg("exit code: %d", r & 0xff);
	return (option_mask32 & FLAG_IGNORE_RETVAL) ? 0 : r;
}
