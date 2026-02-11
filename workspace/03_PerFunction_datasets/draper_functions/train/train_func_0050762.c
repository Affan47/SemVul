absem_wait(void)
{
	int		absem;
	struct sembuf	sops;
	long		now;
	long		start_wait;
	struct timespec	timeout;

	if((absem = absem_get(0)) < 0) {
		perror(__FUNCTION__);
		return absem;
	}
	sops.sem_num = 0;
	sops.sem_op = -1;
	sops.sem_flg = 0;
	start_wait = time(NULL);
	timeout.tv_sec = timeout_seconds;
	timeout.tv_nsec = 0;
	if(semtimedop(absem, &sops, 1, &timeout) < 0) {
		switch(errno) {
		case EIDRM:
			break;
		case EAGAIN:
			fprintf(stderr, "Astribanks waiting timed out\n");
			return -errno;
		default:
			perror("semop");
			return -errno;
		}

	}
	now = time(NULL);
	if(debug)
		fprintf(stderr, "%s: waited on absem %ld seconds\n", progname, now - start_wait);
	if(verbose)
		printf("Finished after %ld seconds\n", now - start_wait);
	return 0;
}
