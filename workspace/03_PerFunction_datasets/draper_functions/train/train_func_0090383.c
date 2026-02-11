write_uint16(int fd, unsigned int uint)
{
	unsigned char upper = (uint >> 8) & 0xff;
	unsigned char lower = (uint) & 0xff;

	if ((write(fd, &upper, 1) < 1)
	    || (write(fd, &lower, 1) < 1)) {
		perror("While writing");
		exit(1);
	}
}
