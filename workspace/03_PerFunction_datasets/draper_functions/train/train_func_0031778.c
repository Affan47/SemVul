ididxtype(id)
int	id;
{
    int		i, n;

    n = sizeof(itypetbl) / sizeof(itypetbl[0]);
    for (i = 0; i < n; i++) {
	if (id >= itypetbl[i].idmin && id <= itypetbl[i].idmax)
	    return itypetbl[i].idxtype;
    }
    return IT_UNKNOWN;
}
