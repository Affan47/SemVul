mono_shared_area_for_pid (void *pid)
{
	int fd;

	int size = mono_pagesize ();
	char buf [128];
	void *res;

	if (shared_area_disabled ())
		return NULL;

	g_snprintf (buf, sizeof (buf), "/mono.%d", GPOINTER_TO_INT (pid));

	fd = shm_open (buf, O_RDONLY, S_IRUSR|S_IRGRP);
	if (fd == -1)
		return NULL;
	res = mmap (NULL, size, PROT_READ, MAP_SHARED, fd, 0);
	if (res == MAP_FAILED) {
		close (fd);
		return NULL;
	}


	close (fd);
	return res;
}
