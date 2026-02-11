get_destination_dir(char *dest_folder)
{
	DIR		   *dir;

	Assert(dest_folder != NULL);
	dir = opendir(dest_folder);
	if (dir == NULL)
	{
		fprintf(stderr, _("%s: could not open directory \"%s\": %s\n"),
				progname, basedir, strerror(errno));
		disconnect_and_exit(1);
	}

	return dir;
}
