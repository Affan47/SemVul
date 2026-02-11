calc_cpu_total()
{
    int total;
#if defined(LINUX)
    char line[BUFFER_LEN] = { '\0' };
    int cpu = 0;
    int nice = 0;
    int system = 0;
    int idle = 0;

    int ps = open("/proc/stat", O_RDONLY);
    int rc = read(ps, line, sizeof(line));
    close(ps);
    if (rc < 0)
        return 0;
    sscanf(line, "%*s %d %d %d %d", &cpu, &nice, &system, &idle);
    total = cpu + nice + system + idle;

#endif

#if defined(FREEBSD)
    struct timeval tv;

    gettimeofday(&tv, 0);
    total = tv.tv_sec * 1000 + tv.tv_usec / 1000;
#endif

    int dt = total - previous_total;
    previous_total = total;

    if (dt < 0)
        dt = 0;

    return dt;
}
