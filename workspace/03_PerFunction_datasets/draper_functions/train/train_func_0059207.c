series_column_width (int v, const DATASET *dset,
				char fmt, int digits)
{
    int namelen = strlen(dset->varname[v]);
    int numlen = max_number_length(v, dset, fmt, digits);

    return (namelen > numlen)? namelen : numlen;
}
