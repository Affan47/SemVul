varnum_from_string (const char *str, DATASET *dset)
{
    int v = positive_int_from_string(str);

    if (v <= 0 || v >= dset->v) {
	v = -1;
    }

    return v;
}
