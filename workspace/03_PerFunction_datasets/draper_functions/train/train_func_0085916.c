explain_buffer_errno_wait4_explanation(explain_string_buffer_t *sb,
    int errnum, const char *syscall_name, int pid, int *status, int options,
    struct rusage *rusage)
{
    switch (errnum)
    {
    case EFAULT:
        if (rusage && explain_is_efault_pointer(rusage, sizeof(*rusage)))
        {
            explain_buffer_efault(sb, "rusage");
            break;
        }
        if (explain_is_efault_pointer(status, sizeof(*status)))
        {
            explain_buffer_efault(sb, "status");
            break;
        }
        break;

    default:
        explain_buffer_errno_waitpid_explanation
        (
            sb,
            errnum,
            syscall_name,
            pid,
            status,
            options
        );
        break;
    }
}
