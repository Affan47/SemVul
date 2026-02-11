egcmp(const void *pa, const void *pb)
{
    const double *a = *(const double *const *)pa;
    const double *b = *(const double *const *)pb;

    if (*a > *b)
	return -1;
    if (*a < *b)
	return 1;

    return 0;
}
