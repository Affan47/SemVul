openf(void)
{
	static int fd = 0;
	Bflush(output);
	Bterm(output);
	if(fd > 0)
		close(fd);
	fd = create(name,OWRITE,0666);
	if(fd < 0) {
		fprint(2, "grep: can't create %s: %r\n", name);
		exits("create");
	}
	Binit(output, fd, OWRITE);
}
