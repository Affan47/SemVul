get_essid(const char *dev, const char *key)
{

    struct iwreq req;
    char key_buffer[32];
    char essid_buffer[IW_ESSID_MAX_SIZE + 1];
    int age;


    qprintf(key_buffer, sizeof(key_buffer), "%s.%s", dev, key);
    age = hash_age(&wireless, key);


    if (age > 0 && age <= HASH_TTL) {
	return (0);
    }

    if (get_ifname(&req, dev) != 0) {
	return (-1);
    }

    memset(essid_buffer, 0, sizeof(essid_buffer));
    req.u.essid.pointer = (caddr_t) essid_buffer;
    req.u.essid.length = IW_ESSID_MAX_SIZE + 1;
    req.u.essid.flags = 0;

    if (do_ioctl(sock, dev, SIOCGIWESSID, &req) < 0) {
	ioctl_error(__LINE__);
	return -1;
    }

    hash_put(&wireless, key_buffer, essid_buffer);
    return (0);

}
