empty_lines(s, e)
	int s;
	int e;
{
	register int i;

	for (i = s;  i <= e;  i++)
		if (table[i] != NULL_POSITION)
			return (0);
	return (1);
}
