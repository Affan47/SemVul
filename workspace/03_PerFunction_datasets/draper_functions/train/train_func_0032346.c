physicalMemory()
{
    int rc;
    struct sysinfo info;

    rc = sysinfo(&info);
    if(rc < 0)
        return -1;

    if(info.totalram <= 0x7fffffff / info.mem_unit)
        return (int)(info.totalram * info.mem_unit);

    return -1;
}
