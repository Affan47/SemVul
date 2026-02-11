_Cpool_writen_timeout(
#ifdef CPOOL_DEBUG
	file,line,
#endif
	fd,vptr,n,timeout)
#ifdef CPOOL_DEBUG
	char *file;
	int line;
#endif
	int fd;
	void *vptr;
	size_t n;
	int timeout;
{
	size_t		nleft;
	ssize_t       nwriten;
	char         *ptr;
	int           save_serrno;


	Sigfunc  *sigfunc;

#ifdef CPOOL_DEBUG
	if (Cpool_debug != 0)
		log(LOG_INFO,"[Cpool  [%2d][%2d]] In _Cpool_writen_timeout(%d,0x%lx,0x%x,%d) called at %s:%d\n",
			_Cpool_self(),_Cthread_self(),fd,(unsigned long) vptr, (unsigned int) n, timeout,
			file,line);
#endif


	if ((sigfunc = _Cpool_signal(SIGALRM, _Cpool_alarm)) == SIG_ERR) {
		serrno = SEINTERNAL;
		return(0);
	}


	_Cpool_signal(SIGPIPE, SIG_IGN);

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		alarm(timeout);
		if ( (nwriten = write(fd, ptr, nleft)) <= 0) {
			if (errno == EINTR) {
				errno = ETIMEDOUT;
				serrno = SETIMEDOUT;
			}
			goto doreturn;
		}
		nleft -= nwriten;
		ptr   += nwriten;
	}
  doreturn:
	save_serrno = serrno;

	alarm(0);

	_Cpool_signal(SIGALRM, sigfunc);
	serrno = save_serrno;
	return(n - nleft);
}
