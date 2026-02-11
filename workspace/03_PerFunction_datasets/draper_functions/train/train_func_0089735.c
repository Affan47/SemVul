i_read(fd,buffer,length,timeout)
int fd;
char *buffer;
int length;
int timeout;
{
	int cc = -2;


	alarm(timeout);

#ifdef HAVE_SIGLONGJMP
	if (1 != sigsetjmp(env,1)) {
#else
	if (1 != setjmp(env)) {
#endif
		env_valid = TRUE;
		cc = read(fd,buffer,length);
	}
	env_valid = FALSE;
	i_read_errno = errno;

	alarm(0);
	return(cc);
}
