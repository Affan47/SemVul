dump_proc_stat (BufferFile *file, int pid)
{
	int  fd;
	char filename[PATH_MAX];

	sprintf (filename, PROC_PATH "/%d/stat", pid);

	fd = open (filename, O_RDONLY);
	if (fd < 0)
		return;

	buffer_file_dump (file, fd);

	close (fd);
}
