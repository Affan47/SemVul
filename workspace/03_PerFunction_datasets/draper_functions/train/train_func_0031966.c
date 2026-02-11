x_vasprintf(char **strp, const char *fmt, va_list args, const char *file,
            int line)
{
    va_list args_copy;
    int status;

    va_copy(args_copy, args);
    status = vasprintf(strp, fmt, args_copy);
    va_end(args_copy);
    while (status < 0) {
        va_copy(args_copy, args);
        status = vsnprintf(NULL, 0, fmt, args_copy);
        va_end(args_copy);
        status = (status < 0) ? 0 : status + 1;
        (*xmalloc_error_handler)("vasprintf", status, file, line);
        va_copy(args_copy, args);
        status = vasprintf(strp, fmt, args_copy);
        va_end(args_copy);
    }
}
