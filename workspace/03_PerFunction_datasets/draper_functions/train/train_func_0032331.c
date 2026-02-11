svc_start_check(void)
{
	RC_SERVICE state;

	state = rc_service_state(service);

	if (in_background) {
		if (!(state & (RC_SERVICE_INACTIVE | RC_SERVICE_STOPPED)))
			exit(EXIT_FAILURE);
		if (rc_yesno(getenv("IN_HOTPLUG")))
			rc_service_mark(service, RC_SERVICE_HOTPLUGGED);
		if (strcmp(runlevel, RC_LEVEL_SYSINIT) == 0)
			ewarnx("WARNING: %s will be started in the"
			    " next runlevel", applet);
	}

	if (exclusive_fd == -1)
		exclusive_fd = svc_lock(applet);
	if (exclusive_fd == -1) {
		if (errno == EACCES)
			eerrorx("%s: superuser access required", applet);
		if (state & RC_SERVICE_STOPPING)
			ewarnx("WARNING: %s is stopping", applet);
		else
			ewarnx("WARNING: %s is already starting", applet);
	}
	fcntl(exclusive_fd, F_SETFD,
	    fcntl(exclusive_fd, F_GETFD, 0) | FD_CLOEXEC);

	if (state & RC_SERVICE_STARTED) {
		ewarn("WARNING: %s has already been started", applet);
		exit(EXIT_SUCCESS);
	}
	else if (state & RC_SERVICE_INACTIVE && !in_background)
		ewarnx("WARNING: %s has already started, but is inactive",
		    applet);

	rc_service_mark(service, RC_SERVICE_STARTING);
	hook_out = RC_HOOK_SERVICE_START_OUT;
	rc_plugin_run(RC_HOOK_SERVICE_START_IN, applet);
}
