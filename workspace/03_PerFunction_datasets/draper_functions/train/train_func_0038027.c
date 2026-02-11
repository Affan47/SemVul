Iwconfig_Get_SSID(const char *in_dev, char *errstr, char *in_essid) {
    struct iwreq wrq;
    int skfd;
    char essid[IW_ESSID_MAX_SIZE + 1];

    if ((skfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        snprintf(errstr, STATUS_MAX, "Failed to create socket to fetch SSID on %s: %s",
                 in_dev, strerror(errno));
        return -1;
    }

    strncpy(wrq.ifr_name, in_dev, IFNAMSIZ);
    wrq.u.essid.pointer = (caddr_t) essid;
    wrq.u.essid.length = IW_ESSID_MAX_SIZE+1;
    wrq.u.essid.flags = 0;

    if (ioctl(skfd, SIOCGIWESSID, &wrq) < 0) {
        snprintf(errstr, STATUS_MAX, "Failed to fetch SSID from %s: %s",
                 in_dev, strerror(errno));
        close(skfd);
        return -1;
    }

    snprintf(in_essid, kismin(IW_ESSID_MAX_SIZE, wrq.u.essid.length) + 1, "%s",
             (char *) wrq.u.essid.pointer);

    close(skfd);
    return 0;
}
