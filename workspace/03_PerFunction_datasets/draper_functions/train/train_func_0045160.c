zrand(void)
{
    int fd;
    int ret;

    if (chrooted != 0 ||
#ifdef PROBE_RANDOM_AT_RUNTIME
        ((fd = open(random_device, O_RDONLY | O_NONBLOCK)) == -1)
#elif defined(HAVE_DEV_ARANDOM)
        ((fd = open("/dev/arandom", O_RDONLY | O_NONBLOCK)) == -1)
#elif defined(HAVE_DEV_URANDOM)
        ((fd = open("/dev/urandom", O_RDONLY | O_NONBLOCK)) == -1)
#else
        ((fd = open("/dev/random", O_RDONLY | O_NONBLOCK)) == -1)
#endif
        ) {
        nax:
#ifdef HAVE_RANDOM
        return (unsigned int) (random() ^ iptropy);
#else
        return (unsigned int) (rand() ^ iptropy);
#endif
    }
    if (read(fd, &ret, sizeof ret) != (ssize_t) sizeof ret) {
        (void) close(fd);
        goto nax;
    }
    (void) close(fd);
    return (unsigned int) (ret ^ iptropy);
}
