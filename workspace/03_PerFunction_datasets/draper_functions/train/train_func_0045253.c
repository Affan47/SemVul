os_mtime_set_errok(string_ty *path, time_t when)
{
    struct utimbuf  utb;

    trace(("os_mtime_set_errok(path = %08lX, when = %ld)\n{\n",
	(long)path, (long)when));
    os_become_must_be_active();
    trace_string(path->str_text);
    trace(("when = %s", ctime(&when)));
    utb.actime = when;
    utb.modtime = when;
    if (glue_utime(path->str_text, &utb))
    {
	sub_context_ty  *scp;
	int             errno_old;

	errno_old = errno;
	scp = sub_context_new();
	sub_errno_setx(scp, errno_old);
	sub_var_set_string(scp, "File_Name", path);
	error_intl(scp, i18n("warning: utime $filename: $errno"));
	sub_context_delete(scp);
    }
    trace(("}\n"));
}
