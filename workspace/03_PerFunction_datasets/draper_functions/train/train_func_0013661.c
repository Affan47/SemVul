explain_buffer_errno_tmpnam_explanation(explain_string_buffer_t *sb, int errnum,
    const char *syscall_name, char *pathname)
{
    char            *tmpbuf;
    const char      *dir;
    const char      *prefix;
    int             try_tmpdir;
    char            tmpbufmem[L_tmpnam];

    tmpbuf = pathname ? pathname : tmpbufmem;
    dir = NULL;
    prefix = 0;
    try_tmpdir = 0;
    if
    (
        errnum != EFAULT
    &&
        explain_path_search(tmpbuf, L_tmpnam, dir, prefix, try_tmpdir) < 0
    &&
        errno == errnum
    &&
        explain_path_search_explanation(sb, errnum, dir, try_tmpdir)
    )
    {
        return;
    }


    switch (errnum)
    {
    case EFAULT:
        explain_buffer_efault(sb, "pathname");
        break;

    case EEXIST:
        explain_buffer_eexist_tempname_dirname(sb, tmpbuf);
        break;

    case EINVAL:
        explain_buffer_einval_mkstemp(sb, tmpbuf, "pathname");
        break;

    default:
        explain_buffer_errno_lstat_explanation
        (
            sb,
            errnum,
            syscall_name,
            tmpbuf,
            0
        );
        break;
    }
    explain_buffer_dangerous_system_call(sb, syscall_name);
}
