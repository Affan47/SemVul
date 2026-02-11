clear_lines(void)
{
	int i;
	for (i = 0; i < linehead; i++)
		free (lines[i].string);
	free (lines);
	linehead = linesize = 0;
	lines = NULL;
}
