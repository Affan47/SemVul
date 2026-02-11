gfs_glob_add(gfs_glob_t *listp, int dtype)
{
	int length = gfs_glob_length(listp);

	if (length >= listp->size) {
		int n = listp->size + GFS_GLOB_DELTA;
		unsigned char *t;

		GFARM_REALLOC_ARRAY(t, listp->array, n);
		if (t == NULL) {
			gflog_debug(GFARM_MSG_1001415,
				"re-allocation of array failed: %s",
				gfarm_error_string(GFARM_ERR_NO_MEMORY));
			return (GFARM_ERR_NO_MEMORY);
		}
		listp->size = n;
		listp->array = t;
	}
	listp->array[length] = dtype;
	listp->length++;
	return (GFARM_ERR_NO_ERROR);
}
