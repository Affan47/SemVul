write_pidfile (const char *pidfile)
{
 	char pid[16];
	int fd;
	gboolean success = FALSE;

	if ((fd = open (pidfile, O_CREAT|O_WRONLY|O_TRUNC, 00644)) < 0) {
		fprintf (stderr, _("Opening %s failed: %s\n"), pidfile, strerror (errno));
		return FALSE;
	}

 	snprintf (pid, sizeof (pid), "%d", getpid ());
	if (write (fd, pid, strlen (pid)) < 0)
		fprintf (stderr, _("Writing to %s failed: %s\n"), pidfile, strerror (errno));
	else
		success = TRUE;

	if (close (fd))
		fprintf (stderr, _("Closing %s failed: %s\n"), pidfile, strerror (errno));

	return success;
}
