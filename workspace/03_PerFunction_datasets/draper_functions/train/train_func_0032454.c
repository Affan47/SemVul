GLEDupFD(int* fd, int dup, int to) {
	if (*fd >= 0) {
		close(fd[1-dup]);
		dup2(fd[dup], to);
		close(fd[dup]);
	}
}
