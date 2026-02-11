gf_string2percent (const char *str, double *n)
{
        double value = 0;
        char *tail = NULL;
        int old_errno = 0;
        const char *s = NULL;

        if (str == NULL || n == NULL) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "argument invalid");
                errno = EINVAL;
                return -1;
        }

        for (s = str; *s != '\0'; s++) {
                if (isspace (*s))
                        continue;
                if (*s == '-')
                        return -1;
                break;
        }

        old_errno = errno;
        errno = 0;
        value = strtod (str, &tail);
        if (str == tail)
                errno = EINVAL;

        if (errno == ERANGE || errno == EINVAL)
                return -1;

        if (errno == 0)
                errno = old_errno;

        if (!((tail[0] == '\0') ||
              ((tail[0] == '%') && (tail[1] == '\0'))))
                return -1;

        *n = value;

        return 0;
}
