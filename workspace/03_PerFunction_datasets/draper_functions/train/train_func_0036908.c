close_sha1_file(int fd)
{
	if (fsync_object_files)
		fsync_or_die(fd, "sha1 file");
	fchmod(fd, 0444);
	if (close(fd) != 0)
		die("unable to write sha1 file");
}
