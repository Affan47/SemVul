gretl_spawn (char *cmdline)
{
    GError *error = NULL;
    gchar *errout = NULL;
    gchar *sout = NULL;
    int ok, status;
    int ret = 0;

    gretl_error_clear();

    ok = g_spawn_command_line_sync(cmdline,
				   &sout,
				   &errout,
				   &status,
				   &error);

    if (!ok) {
	gretl_errmsg_set(error->message);
	fprintf(stderr, "gretl_spawn: '%s'\n", error->message);
	g_error_free(error);
	ret = 1;
    } else if (errout && *errout) {
	fprintf(stderr, "stderr: '%s'\n", errout);
	if (!non_fatal(errout)) {
	    gretl_errmsg_set(errout);
	    fprintf(stderr, "gretl_errmsg: '%s'\n", gretl_errmsg_get());
	    ret = 1;
	}
    } else if (status != 0) {
	if (sout != NULL && *sout) {
	    gretl_errmsg_set(sout);
	    fprintf(stderr, "gretl_spawn: status = %d: '%s'\n", status, sout);
	} else {
	    gretl_errmsg_set(_("Command failed"));
	    fprintf(stderr, "gretl_spawn: status = %d\n", status);
	}
	ret = 1;
    }

    if (errout != NULL) g_free(errout);
    if (sout != NULL) g_free(sout);

    if (ret) {
	fprintf(stderr, "Failed command: '%s'\n", cmdline);
    }

    return ret;
}
