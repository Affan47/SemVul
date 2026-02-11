recv_stepd(int fd)
{
	int i;

	safe_read(fd, &nb_available_files, sizeof(int));
	if (nb_available_files > 0)
		mic_devices = xmalloc(sizeof(int) * nb_available_files);
	for (i = 0; i < nb_available_files; i++)
		safe_read(fd, &mic_devices[i], sizeof(int));
	return;

rwfail:	error("gres_plugin_recv_stepd failed");
}
