reseedrandom() {

	pid_t pid;
	hash_state hs;
	struct timeval tv;

	if (!donerandinit) {
		dropbear_exit("seedrandom not done");
	}

	pid = getpid();
	gettimeofday(&tv, NULL);

	sha1_init(&hs);
	sha1_process(&hs, (void*)hashpool, sizeof(hashpool));
	sha1_process(&hs, (void*)&pid, sizeof(pid));
	sha1_process(&hs, (void*)&tv, sizeof(tv));
	sha1_done(&hs, hashpool);
}
