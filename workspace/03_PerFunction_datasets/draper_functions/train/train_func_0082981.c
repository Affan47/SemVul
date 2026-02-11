os_mtime_set(string_ty *path, time_t when)
{
    struct utimbuf  utb;
    int             err;

    trace(("os_mtime_set(path = %08lX, when = %ld)\n{\n", (long)path,
	(long)when));
    os_become_must_be_active();
    trace_string(path->str_text);
    trace(("when = %s", ctime(&when)));
    utb.actime = when;
    utb.modtime = when;
    err = glue_utime(path->str_text, &utb);
#ifdef __CYGWIN__
    if (err && errno == EACCES)
	err = 0;
#endif
    if (err)
    {
	sub_context_ty  *scp;
	int             errno_old;

	errno_old = errno;
	scp = sub_context_new();
	sub_errno_setx(scp, errno_old);
	sub_var_set_string(scp, "File_Name", path);
	fatal_intl(scp, i18n("utime $filename: $errno"));

    }
    trace(("}\n"));
}
