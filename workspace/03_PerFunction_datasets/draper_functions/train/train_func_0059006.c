_gf_string2long (const char *str, long *n, int base)
{
        long value = 0;
        char *tail = NULL;
        int old_errno = 0;

        if (str == NULL || n == NULL) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "argument invalid");
                errno = EINVAL;
                return -1;
        }

        old_errno = errno;
        errno = 0;
        value = strtol (str, &tail, base);
        if (str == tail)
                errno = EINVAL;

        if (errno == ERANGE || errno == EINVAL)
                return -1;

        if (errno == 0)
                errno = old_errno;

        if (tail[0] != '\0')
                return -1;

        *n = value;

        return 0;
}
