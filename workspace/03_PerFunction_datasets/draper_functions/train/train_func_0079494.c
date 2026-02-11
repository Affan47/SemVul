sysv_writepidfile(int pidfilefd)
{
	pid_t p = getpid();
	char pidbuff[32];
	sprintf(pidbuff, "%d", (int) p);
	int len = strlen(pidbuff) + 1;
	pidbuff[len - 1] = '\n';
	int rc = write(pidfilefd, pidbuff, len);
	if (rc < len) {
		close(pidfilefd);
		return 1;
	}
	close(pidfilefd);
	return 0;
}
