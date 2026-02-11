numColumns(char **row)
{
	int ncols = 0;

	if (!row)
		return -1;
	while (row[ncols++])
		;
	return --ncols;
}
