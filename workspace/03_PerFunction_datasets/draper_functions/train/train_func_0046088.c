daemonize()
{
	int fd=open("/dev/null",O_RDWR);
	if(fork()==0)
	{
		dup2(fd,STDIN_FILENO);
		dup2(fd,STDOUT_FILENO);
		dup2(fd,STDERR_FILENO);
		close(fd);
		setsid();
		umask(0);
	}
	else
	{
		exit(0);
	}
}
