invalid_cmdline(const char * program_name, int err, const char * fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    err = ff_vlog(FC_ERROR, err, fmt, args);
    va_end(args);

    ff_log(FC_NOTICE, 0, "Try `%s --help' for more information", program_name);

    return err ? err : -EINVAL;
}
