explain_buffer_errno_wait4_system_call(explain_string_buffer_t *sb,
    int errnum, int pid, int *status, int options, struct rusage *rusage)
{
    (void)errnum;
    explain_string_buffer_puts(sb, "wait4(pid = ");
    explain_buffer_pid_t(sb, pid);
    if (pid == 0)
    {
        explain_string_buffer_puts(sb, " = process group ");
        explain_buffer_pid_t(sb, getpgrp());
    }
    else if (pid < -1)
    {
        explain_string_buffer_puts(sb, " = process group ");
        explain_buffer_pid_t(sb, -pid);
    }
    explain_string_buffer_puts(sb, ", status = ");
    explain_buffer_pointer(sb, status);
    explain_string_buffer_puts(sb, ", options = ");
    explain_buffer_waitpid_options(sb, options);
    explain_string_buffer_puts(sb, ", rusage = ");
    explain_buffer_pointer(sb, rusage);
    explain_string_buffer_putc(sb, ')');
}
