data_init(dns_engine_param_t *ep)
{
    int fd;
    void *p;
    off_t size;
    data_header_t *header;
    data_config_t *conf = (data_config_t *) ep->ep_conf;

    plog(LOG_DEBUG, "%s: file = %s", MODULE, conf->conf_filename);

    if ((fd = open(conf->conf_filename, O_RDONLY)) < 0) {
        plog(LOG_ERR, "%s: can't open: %s", MODULE, conf->conf_filename);
        return -1;
    }

    size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    p = mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);
    if ((intptr_t) p == -1) {
        plog_error(LOG_ERR, MODULE, "mmap() failed");
        close(fd);
        return -1;
    }

    header = (data_header_t *) p;
    if (data_validate(header, size) < 0) {
        munmap(p, size);
        close(fd);
        return -1;
    }

    plog(LOG_DEBUG, "%s: fd = %d, mmap = %p", MODULE, fd, p);

    conf->conf_fd = fd;
    conf->conf_data = (uint8_t *) p;
    conf->conf_hash = (data_hash_t *) ((uint8_t *) p + sizeof(data_header_t));
    conf->conf_datasize = size;
    conf->conf_hashsize = ntohl(header->df_hashsize);

    plog(LOG_INFO, "%s: zone \"%s\": serial %u", MODULE, ep->ep_zone->z_name, ntohl(header->df_serial));

    return 0;
}
