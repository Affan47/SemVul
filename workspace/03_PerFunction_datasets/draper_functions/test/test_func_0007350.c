pcm_trunc(struct ast_filestream *fs)
{
	int cur, fd;

	if ((fd = fileno(fs->f)) < 0) {
		ast_log(AST_LOG_WARNING, "Unable to determine file descriptor for pcm filestream %p: %s\n", fs, strerror(errno));
		return -1;
	}
	if ((cur = ftello(fs->f)) < 0) {
		ast_log(AST_LOG_WARNING, "Unable to determine current position in pcm filestream %p: %s\n", fs, strerror(errno));
		return -1;
	}

	return ftruncate(fd, cur);
}
