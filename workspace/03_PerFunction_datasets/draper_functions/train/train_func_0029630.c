gretl_list_min_max (const int *list, int *lmin, int *lmax)
{
    if (list == NULL || list[0] == 0) {
	return E_DATA;
    } else {
	int i;

	*lmin = *lmax = list[1];

	for (i=2; i<=list[0]; i++) {
	    if (list[i] < *lmin) {
		*lmin = list[i];
	    }
	    if (list[i] > *lmax) {
		*lmax = list[i];
	    }
	}

	return 0;
    }
}
