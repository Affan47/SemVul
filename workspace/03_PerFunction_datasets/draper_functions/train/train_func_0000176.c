vlog_msgf(int fd, int lf, const char* fmt, va_list ap, int with_errno)
{
    int level = LOG_PRI(lf);
    char buf[1024];

    if (level_ < level)
    {
        return 0;
    }

    if (fd > -1)
    {
        if (dprintf(fd, "%s;", flty_[level]) < 0)
        {
            return -1;
        }

        if (vdprintf(fd, fmt, ap) < 0)
        {
            return -1;
        }

        if (with_errno)
        {
            if (dprintf(fd, " (%s)", strerror(errno)) < 0)
            {
                return -1;
            }
        }

        if (dprintf(fd, "\n") < 0)
        {
            return -1;
        }
    }
    else
    {
        if (vsnprintf(buf, sizeof(buf), fmt, ap) < 0)
        {
            return -1;
        }

        syslog(level | LOG_DAEMON, "%s", buf);
    }

    return 0;
}
