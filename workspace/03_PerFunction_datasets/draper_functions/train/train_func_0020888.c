slave_status(krb5_context context,
	     const char *file,
	     const char *fmt, ...)
{
    char *status = NULL;
    va_list args;
    int len;

    va_start(args, fmt);
    len = vasprintf(&status, fmt, args);
    va_end(args);
    if (len < 0 || status == NULL) {
	unlink(file);
	return;
    }
    krb5_warnx(context, "slave status change: %s", status);

    rk_dumpdata(file, status, len);
    free(status);
}
