Nwrite(_fd, _buf, count)
int _fd;
char *_buf;
int count;
{
    register int cnt;

    if (udp)  {
      again:
	if (atm) cnt = write(_fd, _buf, count);
	else cnt = sendto(_fd, _buf, count, 0, (struct sockaddr *) &sinhim, sizeof(sinhim));
	numCalls++;
	if ( cnt<0 && errno == ENOBUFS )  {
	    delay(18000);
	    errno = 0;
	    goto again;
	}
    } else {
	cnt = write(_fd, _buf, count);
	numCalls++;
    }
if (cnt < 0) perror("WA:write");
    return(cnt);
}
