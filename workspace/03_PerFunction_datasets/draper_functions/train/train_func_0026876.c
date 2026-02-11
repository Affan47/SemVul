p9accept(int cfd, char *dir)
{
	int fd;

	if((fd = _p9netfd(dir)) < 0){
		werrstr("bad 'directory' in accept");
		return -1;
	}

	return dup(fd);
}
