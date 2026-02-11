dsgw_sort_values(
    struct berval	**vals,
    DSGW_VALCMP_CALLBACK *cmp
)
{
    int nel;

    if (!vals) {
	return 0;
    }

    for ( nel = 0; vals[nel] != NULL; nel++ )
	;

    qsort(vals, nel, sizeof(struct berval *), (VOIDCMP_CALLBACK *)cmp);

    return 0;
}
