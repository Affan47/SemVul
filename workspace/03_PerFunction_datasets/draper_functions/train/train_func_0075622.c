read_data(void* buf, int buf_len, int fd)
{
    fd_set fds;
    int rr;
    int try;
    int have_len = 0;
    struct timeval tv;

    FD_ZERO(&fds);
    FD_SET(fd,&fds);
    tv.tv_sec = tac_timeout;
    tv.tv_usec = 0;
    try = 0;
    while (have_len < buf_len && try++ < tac_maxtry)
    {
        rr = select(fd+1, &fds, NULL, NULL, &tv);
        if (FD_ISSET(fd, &fds))
	{
	    ssize_t read_len = read(fd,buf+have_len,buf_len-have_len);
	    if (read_len == 0)
	    {

		return -1;
	    }
	    else if (read_len == -1)
	    {
		myerror("read error");
		return -1;
	    }
	    have_len += read_len;
	    if (buf_len != have_len)
		continue;

	    return 0;
        }
    }
    myerror("too many retries");
    return -1;
}
