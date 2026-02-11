netsnmp_access_interface_ioctl_flags_set(int fd,
                                         netsnmp_interface_entry *ifentry,
                                         unsigned int flags, int and_complement)
{
    struct ifreq    ifrq;
    int ourfd = -1, rc = 0;

    DEBUGMSGTL(("access:interface:ioctl", "flags_set\n"));


    if((NULL == ifentry) || (NULL == ifentry->name)) {
        snmp_log(LOG_ERR, "invalid ifentry\n");
        return -1;
    }


    if(fd < 0) {
        fd = ourfd = socket(AF_INET, SOCK_DGRAM, 0);
        if(ourfd < 0) {
            snmp_log(LOG_ERR,"couldn't create socket\n");
            return -2;
        }
    }

    strncpy(ifrq.ifr_name, ifentry->name, sizeof(ifrq.ifr_name));
    ifrq.ifr_name[ sizeof(ifrq.ifr_name)-1 ] = 0;
    rc = ioctl(fd, SIOCGIFFLAGS, &ifrq);
    if(rc < 0) {
        snmp_log(LOG_ERR,"error getting flags\n");
        close(fd);
        return -3;
    }
    if(0 == and_complement)
        ifrq.ifr_flags |= flags;
    else
        ifrq.ifr_flags &= ~flags;
    rc = ioctl(fd, SIOCSIFFLAGS, &ifrq);
    if(rc < 0) {
        close(fd);
        snmp_log(LOG_ERR,"error setting flags\n");
        ifentry->os_flags = 0;
        return -4;
    }

    if(ourfd >= 0)
        close(ourfd);

    ifentry->os_flags = ifrq.ifr_flags;

    return 0;
}
