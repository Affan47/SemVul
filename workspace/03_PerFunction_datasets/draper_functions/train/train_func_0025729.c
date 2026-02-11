gkr_pam_client_run_operation (struct passwd *pwd, const char *control,
                              int op, int argc, const char* argv[])
{
	struct sigaction ignpipe, oldpipe, defchld, oldchld;
	int res;
	pid_t pid;
	int status;


	memset (&ignpipe, 0, sizeof (ignpipe));
	memset (&oldpipe, 0, sizeof (oldpipe));
	ignpipe.sa_handler = SIG_IGN;
	sigaction (SIGPIPE, &ignpipe, &oldpipe);

	memset (&defchld, 0, sizeof (defchld));
	memset (&oldchld, 0, sizeof (oldchld));
	defchld.sa_handler = SIG_DFL;
	sigaction (SIGCHLD, &defchld, &oldchld);

	if (pwd->pw_uid == getuid () && pwd->pw_gid == getgid () &&
	    pwd->pw_uid == geteuid () && pwd->pw_gid == getegid ()) {


		res = keyring_daemon_op (control, op, argc, argv);

	} else {


		switch (pid = fork ()) {
		case -1:
			syslog (GKR_LOG_ERR, "gkr-pam: couldn't fork: %s",
			        strerror (errno));
			res = GKD_CONTROL_RESULT_FAILED;
			break;

		case 0:

			if (setgid (pwd->pw_gid) < 0 || setuid (pwd->pw_uid) < 0 ||
			    setegid (pwd->pw_gid) < 0 || seteuid (pwd->pw_uid) < 0) {
				syslog (GKR_LOG_ERR, "gkr-pam: couldn't switch to user: %s: %s",
				        pwd->pw_name, strerror (errno));
				exit (GKD_CONTROL_RESULT_FAILED);
			}

			res = keyring_daemon_op (control, op, argc, argv);
			exit (res);
			return 0;

		default:

			if (wait (&status) != pid) {
				syslog (GKR_LOG_ERR, "gkr-pam: couldn't wait on child process: %s",
				        strerror (errno));
				res = GKD_CONTROL_RESULT_FAILED;
			}

			res = WEXITSTATUS (status);
			break;
		};
	}

	sigaction (SIGCHLD, &oldchld, NULL);
	sigaction (SIGPIPE, &oldpipe, NULL);

	return res;
}
