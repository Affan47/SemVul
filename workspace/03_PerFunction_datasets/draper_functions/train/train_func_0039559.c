floppyd_writer(int fd, char* buffer, int len)
{
	Dword errcode;
	Dword gotlen;
	Byte buf[16];

	dword2byte(1, buf);
	buf[4] = OP_WRITE;
	dword2byte(len, buf+5);

	if(write(fd, buf, 9) < 9)
		return AUTH_IO_ERROR;
	if(write(fd, buffer, len) < len)
		return AUTH_IO_ERROR;

	if (read_dword(fd) != 8) {
		errno = EIO;
		return -1;
	}

	gotlen = read_dword(fd);
	errcode = read_dword(fd);

	errno = errcode;
	if(errno != 0 && gotlen == 0) {
	    if (errno == EBADF)
		errno = EROFS;
	    gotlen = -1;
	}

	return gotlen;
}
