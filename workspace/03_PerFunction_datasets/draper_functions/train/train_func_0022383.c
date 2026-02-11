fgetoffset(n, fd)
long n;
int fd;
{
	u_char buf[4];
	off_t ofs;

	ofs = dictoffset(n);
	if (!skread(fd, ofs, buf, sizeof(buf))) return((off_t)-1);
	ofs = dictoffset(dicttblent + 1) + getdword(buf, 0);

	return(ofs);
}
