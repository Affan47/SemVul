if_eui64(char *ifname, unsigned char *eui)
{
    int s, rc;
    struct ifreq ifr;

    s = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    if(s < 0) return -1;
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));
    rc = ioctl(s, SIOCGIFHWADDR, &ifr);
    if(rc < 0) {
        int saved_errno = errno;
        close(s);
        errno = saved_errno;
        return -1;
    }
    close(s);

    switch(ifr.ifr_hwaddr.sa_family) {
    case ARPHRD_ETHER:
    case ARPHRD_FDDI:
    case ARPHRD_IEEE802_TR:
    case ARPHRD_IEEE802: {
        unsigned char *mac;
        mac = (unsigned char *)ifr.ifr_hwaddr.sa_data;

        if(memcmp(mac, zeroes, 6) == 0 ||
           (mac[0] & 1) != 0 || (mac[0] & 2) != 0) {
            errno = ENOENT;
            return -1;
        }
        memcpy(eui, mac, 3);
        eui[3] = 0xFF;
        eui[4] = 0xFE;
        memcpy(eui + 5, mac + 3, 3);
        eui[0] ^= 2;
        return 1;
    }
    case ARPHRD_EUI64:
    case ARPHRD_IEEE1394:
    case ARPHRD_INFINIBAND: {
        unsigned char *mac;
        mac = (unsigned char *)ifr.ifr_hwaddr.sa_data;
        if(memcmp(mac, zeroes, 8) == 0 ||
           (mac[0] & 1) != 0 || (mac[0] & 2) != 0) {
            errno = ENOENT;
            return -1;
        }
        memcpy(eui, mac, 64);
        eui[0] ^= 2;
        return 1;
    }
    default:
        errno = ENOENT;
        return -1;
    }
}
