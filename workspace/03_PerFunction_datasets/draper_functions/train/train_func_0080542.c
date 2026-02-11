_netsnmp_ioctl_ipaddress_set_v4(netsnmp_ipaddress_entry * entry)
{
    struct ifreq                   ifrq;
    struct sockaddr_in            *sin;
    int                            rc, fd = -1;
    _ioctl_extras                 *extras;

    if (NULL == entry)
        return -1;

    netsnmp_assert(4 == entry->ia_address_len);

    extras = netsnmp_ioctl_ipaddress_extras_get(entry);
    if (NULL == extras)
        return -1;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd < 0) {
        snmp_log(LOG_ERR,"couldn't create socket\n");
        return -2;
    }
    memset(&ifrq, 0, sizeof(ifrq));

    if ('\0' == extras->name[0]) {
        const char *name = netsnmp_access_interface_name_find(entry->if_index);
        int   alias_idx;

        if (NULL == name) {
            DEBUGMSGT(("access:ipaddress:set",
                       "cant find name for index %" NETSNMP_PRIo "d\n",
                       entry->if_index));
            close(fd);
            return -1;
        }


        alias_idx = _next_alias(name);
        snprintf(ifrq.ifr_name,sizeof(ifrq.ifr_name), "%s:%d",
                 name, alias_idx);
    }
    else
        strncpy(ifrq.ifr_name, (char *) extras->name, sizeof(ifrq.ifr_name));

    ifrq.ifr_name[ sizeof(ifrq.ifr_name)-1 ] = 0;

    sin = (struct sockaddr_in*)&ifrq.ifr_addr;
    sin->sin_family = AF_INET;
    memcpy(&sin->sin_addr.s_addr, entry->ia_address,
           entry->ia_address_len);

    rc = ioctl(fd, SIOCSIFADDR, &ifrq);
    close(fd);
    if(rc < 0) {
        snmp_log(LOG_ERR,"error setting address\n");
        return -3;
    }

    return 0;
}
