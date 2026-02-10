fdUpdateBiggest(int fd, int opening)
{
    if (fd < Biggest_FD)
	return;
    assert(fd < Squid_MaxFD);
    if (fd > Biggest_FD) {


	assert(opening);
	Biggest_FD = fd;
	return;
    }


    assert(!opening);
    while (!fd_table[Biggest_FD].flags.open && Biggest_FD > 0)
	Biggest_FD--;
}
