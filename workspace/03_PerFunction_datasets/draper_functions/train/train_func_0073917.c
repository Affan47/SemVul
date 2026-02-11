brasero_transcode_pad_pipe (BraseroTranscode *transcode, GError **error)
{
	int fd;
	gboolean result;

	brasero_job_get_fd_out (BRASERO_JOB (transcode), &fd);
	fd = dup (fd);

	result = brasero_transcode_pad (transcode, fd, error);
	if (result)
		close (fd);

	return result;
}
