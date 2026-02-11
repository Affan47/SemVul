ttyOpen(char *name,int length) {
	int fd;
	struct termios options;
	fd=open(name,O_RDWR);
	if(fd!=-1) {

		fcntl(fd,F_SETFL,0);
		tcgetattr(fd,&options);
		cfmakeraw(&options);
		tcsetattr(fd,TCSANOW,&options);
	}
	return(fd);
}
