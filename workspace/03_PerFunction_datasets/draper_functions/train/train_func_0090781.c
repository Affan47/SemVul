explain_buffer_errno_fflush_explanation(explain_string_buffer_t *sb,
    int errnum, const char *syscall_name, FILE *fp)
{
    int             fildes;


    switch (errnum)
    {
    case EBADF:
    case EINVAL:
        explain_buffer_ebadf_stream(sb, "fp");
        break;

    default:
        fildes = explain_stream_to_fildes(fp);
        explain_buffer_errno_write_explanation
        (
            sb,
            errnum,
            syscall_name,
            fildes,
            NULL,
            0
        );
        break;
    }
}
