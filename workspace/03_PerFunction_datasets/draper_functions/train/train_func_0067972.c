mutate_lease(char *fn, const unsigned char *ipv4, struct lease_entry *entry)
{
    int fd;
    unsigned lease_orig, lease_time;
    int rc;
    struct timeval now, real;
    time_t stable;
    int clock_status;
    time_t orig;

    gettime(&now, &stable);
    get_real_time(&real, &clock_status);

    if(clock_status != CLOCK_TRUSTED)
        return -1;

    if(entry && entry->address != ipv4_address(ipv4)) {
        fprintf(stderr, "Entry mismatch when mutating!\n");
        return -1;
    }

    fd = open(fn, O_RDWR);
    if(fd < 0)
        return 0;

    rc = read_lease_file(fd, ipv4, &lease_orig, &lease_time, NULL, NULL, 0);
    if(rc < 0)
        goto fail;

    if(lease_orig != 0)
        goto fail;

    if(entry && stable >= lease_time)
        orig = real.tv_sec - (entry->lease_end_m - now.tv_sec);
    else
        orig = real.tv_sec;

    if(orig > 1000000000 && orig <= real.tv_sec + 300)
        lease_orig = orig;
    else
        lease_orig = real.tv_sec;

    rc = update_lease_file(fd, lease_orig, lease_time);
    if(rc < 0)
        goto fail;

    if(entry)
        entry->lease_orig = lease_orig;

    close_lease_file(fd, 1);
    return 1;

 fail:
    close_lease_file(fd, 0);
    return 0;
}
