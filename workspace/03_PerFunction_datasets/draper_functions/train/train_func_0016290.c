explain_buffer_errno_getchar_explanation(explain_string_buffer_t *sb,
    int errnum)
{
    int             fildes;

    if (errnum == EBADF)
    {


        if (explain_libio_no_reads(stdin))
        {
            explain_buffer_ebadf_not_open_for_reading(sb, "fp", -1);
            explain_buffer_software_error(sb);
            return;
        }
    }

    fildes = fileno(stdin);
    explain_buffer_errno_read_explanation
    (
        sb,
        errnum,
        "getchar",
        fildes,
        NULL,
        0
    );
}
