copy_subsample_mask (const char *src, int *err)
{
    char *ret = NULL;

    if (src == RESAMPLED) {
	ret = RESAMPLED;
    } else if (src != NULL) {
	int n = get_submask_length(src);

	ret = malloc(n * sizeof *ret);
	if (ret != NULL) {
	    memcpy(ret, src, n);
	} else {
	    *err = E_ALLOC;
	}
    }

    return ret;
}
