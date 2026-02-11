do_construct() {
	check(fd);
	schedule(EPOLLIN|EPOLLET);
	setReadAheadBufferSize(sizeof(line));
	setWriteBufferSize(4*1024);
}
