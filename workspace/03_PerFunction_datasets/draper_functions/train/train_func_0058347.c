get_random_bytes(unsigned char *data, unsigned int length)
{

	long r;
        unsigned n;
	int fd, r_size = sizeof(r);

	fd = open("/dev/urandom", O_RDONLY);
        while (length > 0) {

		if (fd == -1 || read(fd, &r, r_size) != r_size)
			r = rand();
                r = r ^ (r >> 8);
                r = r ^ (r >> 4);
                n = r & 0x7;

		if (fd == -1 || read(fd, &r, r_size) != r_size)
			r = rand();
                r = r ^ (r >> 8);
                r = r ^ (r >> 5);
                n = (n << 3) | (r & 0x7);

		if (fd == -1 || read(fd, &r, r_size) != r_size)
			r = rand();
                r = r ^ (r >> 8);
                r = r ^ (r >> 5);
                n = (n << 2) | (r & 0x3);

                *data++ = n;
                length--;
        }
	if (fd)
		close(fd);
}
