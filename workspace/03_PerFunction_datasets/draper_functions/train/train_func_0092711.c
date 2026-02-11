explain_buffer_errno_getc_explanation(explain_string_buffer_t *sb,
    int errnum, FILE *fp)
{
    int             fildes;

    if (!fp)
    {
        explain_buffer_is_the_null_pointer(sb, "fp");
        return;
    }

    if (errnum == EBADF)
    {


        if (explain_libio_no_reads(fp))
        {
            explain_buffer_ebadf_not_open_for_reading(sb, "fp", -1);
            explain_buffer_software_error(sb);
            return;
        }
    }

    fildes = explain_stream_to_fildes(fp);
    if (errnum == EBADF)
    {
        explain_buffer_ebadf(sb, fildes, "fp");
        return;
    }

    explain_buffer_errno_read_explanation(sb, errnum, "getc", fildes, NULL, 0);
}
