write_packet(int  fd, const char* name, apacket** ppacket)
{
    char *p = (char*) ppacket;
    int r, len = sizeof(ppacket);
    char buff[8];
    if (!name) {
        snprintf(buff, sizeof buff, "fd=%d", fd);
        name = buff;
    }

#if ADB_TRACE
    if (ADB_TRACING) {
        dump_packet(name, "to remote", *ppacket);
    }
#endif
    len = sizeof(ppacket);
    while(len > 0) {
        r = adb_write(fd, p, len);
        if(r > 0) {
            len -= r;
            p += r;
        } else {
            D("%s: write_packet (fd=%d) error ret=%d errno=%d: %s\n", name, fd, r, errno, strerror(errno));
            if((r < 0) && (errno == EINTR)) continue;
            return -1;
        }
    }
    return 0;
}
