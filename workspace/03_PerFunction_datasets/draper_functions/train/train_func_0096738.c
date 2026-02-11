xmalloc(size_t bytes)
{
	void *p;

	if ((p = malloc(bytes)) == NULL) {
		if (sent_sigstop) kill(-1, SIGCONT);
		nsyslog(LOG_ERR, "out of memory");
		exit(1);
	}
	return p;
}
