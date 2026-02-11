gretl_shell (const char *arg, PRN *prn)
{
    int async = 0;
    int err = 0;

    if (arg == NULL || *arg == '\0') {
	return 0;
    }

    if (!libset_get_bool(SHELL_OK)) {
	gretl_errmsg_set(_("The shell command is not activated."));
	return 1;
    }

    if (!strncmp(arg, "launch ", 7)) {
	async = 1;
	arg += 7;
    } else if (*arg == '!') {
	arg++;
    }

    arg += strspn(arg, " \t");

    if (async) {
	err = gretl_shell_async(arg, prn);
    } else {
	err = gretl_shell_sync(arg, NULL, prn);
    }

    return err;
}
