balignfn(htmldata_t * p, char *v)
{
    int rv = 0;
    char c = toupper(*v);
    if ((c == 'L') && !strcasecmp(v + 1, "EFT"))
	p->flags |= BALIGN_LEFT;
    else if ((c == 'R') && !strcasecmp(v + 1, "IGHT"))
	p->flags |= BALIGN_RIGHT;
    else if ((c != 'C') || strcasecmp(v + 1, "ENTER"))
	rv = 1;
    if (rv)
	agerr(AGWARN, "Illegal value %s for BALIGN in TD - ignored\n", v);
    return rv;
}
