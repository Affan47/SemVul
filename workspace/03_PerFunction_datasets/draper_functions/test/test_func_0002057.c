terule_reset(poldiff_t * diff, terule_offset_e idx)
{
	int error = 0;
	terule_destroy(&diff->terule_diffs[idx]);
	diff->terule_diffs[idx] = terule_create();
	if (diff->terule_diffs[idx] == NULL) {
		error = errno;
		ERR(diff, "%s", strerror(error));
		errno = error;
		return -1;
	}
	return 0;
}
