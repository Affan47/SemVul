explain_buffer_errno_fstat_explanation(explain_string_buffer_t *sb,
    int errnum, const char *syscall_name, int fildes, const struct stat *data)
{
    (void)data;
    switch (errnum)
    {
    case EBADF:
        explain_buffer_ebadf(sb, fildes, "fildes");
        break;

    case ENOMEM:
        explain_buffer_enomem_kernel(sb);
        break;

    default:
        explain_buffer_errno_generic(sb, errnum, syscall_name);
        break;
    }
}
