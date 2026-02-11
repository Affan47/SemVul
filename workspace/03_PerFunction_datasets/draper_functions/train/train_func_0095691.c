ns_cprint(register const u_char *cp)
{
	register u_int i;

	if (!TTEST2(*cp, 1))
		return (NULL);
	i = *cp++;
	if (fn_printn(cp, i, snapend))
		return (NULL);
	return (cp + i);
}
