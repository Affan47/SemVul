copyvec (const double *src, int n)
{
    double *targ = NULL;
    size_t sz = n * sizeof *targ;

    if (n > 0 && src != NULL) {
	targ = malloc(sz);
    }

    if (targ != NULL) {
	memcpy(targ, src, sz);
    }

    return targ;
}
