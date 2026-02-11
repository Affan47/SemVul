netsnmp_access_interface_ioctl_ifindex_get(int fd, const char *name)
{
#ifndef SIOCGIFINDEX
    return 0;
#else
    struct ifreq    ifrq;
    int rc = 0;

    DEBUGMSGTL(("access:interface:ioctl", "ifindex_get\n"));

    rc = _ioctl_get(fd, SIOCGIFINDEX, &ifrq, name);
    if (rc < 0) {
        DEBUGMSGTL(("access:interface:ioctl",
                   "ifindex_get error on inerface '%s'\n", name));
        return 0;
    }

#if defined(__FreeBSD__)
    return ifrq.ifr_index;
#else
    return ifrq.ifr_ifindex;
#endif
#endif
}
