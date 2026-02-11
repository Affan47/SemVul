gretl_bundle_get_scalar (gretl_bundle *bundle,
				const char *key,
				int *err)
{
    double x = NADBL;
    GretlType type;
    void *ptr;

    ptr = gretl_bundle_get_data(bundle, key, &type, NULL, err);
    if (!*err && type != GRETL_TYPE_DOUBLE) {
	*err = E_TYPES;
    }

    if (!*err) {
	double *px = (double *) ptr;

	x = *px;
    }

    return x;
}
