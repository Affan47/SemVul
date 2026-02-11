update_lease_file(int fd, unsigned lease_orig, unsigned lease_time)
{
    off_t lrc;
    int rc, i;
    struct iovec iov[2];

    lease_orig = htonl(lease_orig);
    lease_time = htonl(lease_time);

    lrc = lseek(fd, 12, SEEK_SET);
    if(lrc < 0) {
        perror("lseek(lease_file)");
        return -1;
    }

    i = 0;
    iov[i].iov_base = &lease_orig;
    iov[i++].iov_len = 4;
    iov[i].iov_base = &lease_time;
    iov[i++].iov_len = 4;

    rc = writev(fd, iov, i);
    if(rc < 8) {
        perror("write(lease_file)");
        return -1;
    }

    return 1;
}
