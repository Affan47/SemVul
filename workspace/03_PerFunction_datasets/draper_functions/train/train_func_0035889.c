nlspec_set_t1_t2 (nlspec *spec, int t1, int t2)
{
    if (spec != NULL) {
	spec->t1 = t1;
	spec->t2 = t2;
	spec->nobs = t2 - t1 + 1;
    }
}
