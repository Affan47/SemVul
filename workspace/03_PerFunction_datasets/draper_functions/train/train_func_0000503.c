uptime(void)
{
#ifdef __FreeBSD__
    struct timeval boottime;
    time_t now;
    int mib[2];
    size_t size;
    time_t u;
    static char buf[1025];

    (void)time(&now);

    mib[0] = CTL_KERN;
    mib[1] = KERN_BOOTTIME;
    size = sizeof(boottime);
    if (sysctl(mib, 2, &boottime, &size, NULL, 0) != -1 &&
        boottime.tv_sec != 0) {
        u = now - boottime.tv_sec;
        if (u > 60)
            u += 30;

        if (SNCHECK(snprintf(buf, sizeof buf, "%lu days, %lu:%02lu:%02lu",
                             u / 86400UL, u / 3600UL % 24UL,
                             u / 60UL % 60UL, u % 60UL),
                    sizeof buf)) {
            _exit(EXIT_FAILURE);
        }
    }
    return buf;
#else
    int f;
    ssize_t r;
    unsigned long u;
    static char buf[1025];

    if ((f = open("/proc/uptime", O_RDONLY)) == -1) {
        return "?";
    }
    while ((r = read(f, buf, sizeof buf - 1U)) < (ssize_t) 0 && errno == EINTR);
    if (r <= (ssize_t) 0) {
        close(f);
        return "?";
    }
    close(f);
    u = strtoul(buf, NULL, 10);
    if (SNCHECK(snprintf(buf, sizeof buf, "%lu days, %lu:%02lu:%02lu",
                         u / 86400UL, u / 3600UL % 24UL,
                         u / 60UL % 60UL, u % 60UL),
                sizeof buf)) {
        _exit(EXIT_FAILURE);
    }
    return buf;
#endif
}
