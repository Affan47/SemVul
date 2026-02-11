default_handler (int signum)
{
	int i;
	for (i = 0; i < NUM_SIGNALS; ++i) {
		int fd;
		signal_info* h = &signals [i];
		if (mph_int_get (&h->signum) != signum)
			continue;

		mph_int_inc (&h->count);

		if (!acquire_pipelock_handler (&h->pipelock))
			continue;

		fd = mph_int_get (&h->write_fd);
		if (fd > 0) {
			int j,pipecounter;
			char c = signum;
			pipecounter = mph_int_get (&h->pipecnt);
			for (j = 0; j < pipecounter; ++j) {
				int r;
				do { r = write (fd, &c, 1); } while (keep_trying (r));
			}
		}
		release_pipelock_handler (&h->pipelock);
	}
}
