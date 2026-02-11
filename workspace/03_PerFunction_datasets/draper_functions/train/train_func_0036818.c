older_than(int x, int y, int z)
{

	if (sf_major < x) return (TRUE);
	if (sf_major > x) return (FALSE);


	if (sf_minor < y) return (TRUE);
	if (sf_minor > y) return (FALSE);


	if (sf_patch < z) return (TRUE);
	if (sf_patch > z) return (FALSE);


	return (FALSE);
}
