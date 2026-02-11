fixedsizefn(htmldata_t * p, char *v)
{
    int rv = 0;
    char c = toupper(*(unsigned char *) v);
    if ((c == 'T') && !strcasecmp(v + 1, "RUE"))
	p->flags |= FIXED_FLAG;
    else if ((c != 'F') || strcasecmp(v + 1, "ALSE")) {
	agerr(AGWARN, "Illegal value %s for FIXEDSIZE - ignored\n", v);
	rv = 1;
    }
    return rv;
}
