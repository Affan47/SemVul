unlink_or_warn(const char *file)
{
	int rc = unlink(file);

	if (rc < 0) {
		int err = errno;
		if (ENOENT != err) {
			warning("unable to unlink %s: %s",
				file, strerror(errno));
			errno = err;
		}
	}
	return rc;
}
