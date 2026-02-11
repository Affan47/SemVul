main(void)
{
	int i, fd;
	char buff[5] = "AAAA";
	if( (fd=open("./exlog", O_WRONLY | O_CREAT | O_APPEND)) < 0) {
		if(errno == EEXIST) {
			perror("exist!");
			return -1;
		}
	}
	else {
		for(i=0;i<100000;i++) {

			write(fd, buff, 4);
		}
	}
	close(fd);
	return 0;
}
