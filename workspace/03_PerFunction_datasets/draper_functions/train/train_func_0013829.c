colspanfn(htmlcell_t * p, char *v)
{
    long u;

    if (doInt(v, "COLSPAN", 0, MAX_USHORT, &u))
	return 1;
    if (u == 0) {
	agerr(AGWARN, "COLSPAN value cannot be 0 - ignored\n");
	return 1;
    }
    p->cspan = (unsigned short) u;
    return 0;
}
