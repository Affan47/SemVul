fdfp2f(fd,fp)
int fd;
FILE *fp;
{
	if (fd == -1) return(fs + fileno(fp));
	else return(fs + fd);
}
