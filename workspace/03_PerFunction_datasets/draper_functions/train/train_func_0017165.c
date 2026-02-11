open_pcap(char *fname)
{
        int fd;
        struct pcap_file_header pfh;

        memset(&pfh, 0, sizeof(pfh));
        pfh.magic           = TCPDUMP_MAGIC;
        pfh.version_major   = PCAP_VERSION_MAJOR;
        pfh.version_minor   = PCAP_VERSION_MINOR;
        pfh.thiszone        = 0;
        pfh.sigfigs         = 0;
        pfh.snaplen         = 65535;
        pfh.linktype        = LINKTYPE_IEEE802_11;

        fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC,
                  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (fd == -1)
                err(1, "open(%s)", fname);

        if (write(fd, &pfh, sizeof(pfh)) != sizeof(pfh))
                err(1, "write()");

        return fd;
}
