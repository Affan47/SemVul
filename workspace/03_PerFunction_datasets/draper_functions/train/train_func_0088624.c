CheckDistribution(p)
    register char	*p;
{
    static char		SEPS[] = " \t,";
    register STRING	*dp;

    if ((p = strtok(p, SEPS)) == NULL)
	return "Can't parse Distribution line.";
    do {
	for (dp = BadDistribs; *dp; dp++)
	    if (wildmat(p, *dp)) {
		(void)sprintf(Error, "Illegal distribution \"%s\"", MaxLength(p,p));
		return Error;
	    }
    } while ((p = strtok((char *)NULL, SEPS)) != NULL);
    return NULL;
}
