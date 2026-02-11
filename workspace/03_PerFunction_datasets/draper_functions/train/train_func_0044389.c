istgt_lu_dvd_open(ISTGT_LU_DVD *spec, int flags, int mode)
{
	int rc;

	rc = open(spec->file, flags, mode);
	if (rc < 0) {
		return -1;
	}
	spec->fd = rc;
	return 0;
}
