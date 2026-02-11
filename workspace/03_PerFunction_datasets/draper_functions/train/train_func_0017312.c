setup_environment (char ***env, const struct passwd *pwd)
{
    int i, j, path;
    char **e;

    i = 0;
    path = 0;
    *env = NULL;

    i = read_environment(_PATH_ETC_ENVIRONMENT, env);
    e = *env;
    for (j = 0; j < i; j++) {
	if (!strncmp(e[j], "PATH=", 5)) {
	    path = 1;
	}
    }

    e = *env;
    e = realloc(e, (i + 7) * sizeof(char *));

    if (asprintf (&e[i++], "USER=%s",  pwd->pw_name) == -1)
	syslog_and_die ("asprintf: out of memory");
    if (asprintf (&e[i++], "HOME=%s",  pwd->pw_dir) == -1)
	syslog_and_die ("asprintf: out of memory");
    if (asprintf (&e[i++], "SHELL=%s", pwd->pw_shell) == -1)
	syslog_and_die ("asprintf: out of memory");
    if (! path) {
	if (asprintf (&e[i++], "PATH=%s",  _PATH_DEFPATH) == -1)
	    syslog_and_die ("asprintf: out of memory");
    }
    asprintf (&e[i++], "SSH_CLIENT=only_to_make_bash_happy");
    if (do_unique_tkfile)
	if (asprintf (&e[i++], "KRB5CCNAME=%s", tkfile) == -1)
	    syslog_and_die ("asprintf: out of memory");
    e[i++] = NULL;
    *env = e;
}
