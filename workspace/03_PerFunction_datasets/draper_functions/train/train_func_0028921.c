close_target_file(void)
{
	if (dstfd == -1)
		return;

	if (close(dstfd) != 0)
		pg_fatal("could not close target file \"%s\": %s\n",
				 dstpath, strerror(errno));

	dstfd = -1;

}
