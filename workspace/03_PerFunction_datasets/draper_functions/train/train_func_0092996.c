gretl_list_copy (const int *src)
{
    int *targ = NULL;

    if (src != NULL) {
	int n = src[0] + 1;

	targ = malloc(n * sizeof *targ);
	if (targ != NULL) {
	    memcpy(targ, src, n * sizeof *targ);
	}
    }

    return targ;
}
