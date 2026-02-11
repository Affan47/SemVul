is_infinite(double val)
{
	int			inf = isinf(val);

	if (inf == 0)
		return 0;

	if (val > 0)
		return 1;

	return -1;
}
