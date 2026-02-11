click_random_srandom()
{
    static const int bufsiz = 64;
    union {
	char c[bufsiz];
	uint32_t u32[bufsiz / 4];
    } buf;
    int pos = 0;

    ((Timestamp *) (buf.c + pos))->set_now();
    pos += sizeof(Timestamp);

#if CLICK_USERLEVEL
# ifdef O_NONBLOCK
    int fd = open("/dev/random", O_RDONLY | O_NONBLOCK);
# elif defined(O_NDELAY)
    int fd = open("/dev/random", O_RDONLY | O_NDELAY);
# else
    int fd = open("/dev/random", O_RDONLY);
# endif
    if (fd >= 0) {
	ssize_t amt = read(fd, buf.c + pos, bufsiz - pos);
	close(fd);
	if (amt > 0)
	    pos += amt;
    }

    struct {
	pid_t p;
	uid_t u;
    } pu;
    pu.p = getpid();
    pu.u = getuid();
    int pu_amt = (bufsiz - pos < (int) sizeof(pu) ? bufsiz - pos : (int) sizeof(pu));
    memcpy(buf.c + pos, &pu, pu_amt);
    pos += pu_amt;
#endif

    uint32_t result = 0;
    for (int i = 0; i < pos / 4; i++) {
	result ^= buf.u32[i];
	result = (result << 1) | (result >> 31);
    }
    click_srandom(result);
}
