get_mac_address(unsigned char macaddr[MAC_ADDRESS_MAX_LEN], const char *interface = "eth0")
{
    bool result = false;
    const int dummy = socket(AF_INET, SOCK_STREAM, 0);
    if (dummy >= 0)
    {
        struct ifreq r;
        strncpy((char *)r.ifr_name, interface, sizeof r.ifr_name - 1);
        r.ifr_name[sizeof r.ifr_name - 1] = 0;
        if (ioctl(dummy, SIOCGIFHWADDR, &r) >= 0)
        {
            memcpy(macaddr, r.ifr_hwaddr.sa_data, MAC_ADDRESS_MAX_LEN);
            result = true;
        }
        close(dummy);
    }
    return result;
}
