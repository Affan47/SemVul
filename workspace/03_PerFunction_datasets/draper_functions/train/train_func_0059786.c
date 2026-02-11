fixorder(line1, char1, line2, char2)
register LinePtr	*line1,
		*line2;
register int	*char1,
		*char2;
{
	LinePtr	tline;
	int	tchar;

	if (inorder(*line1, *char1, *line2, *char2))
		return NO;

	tline = *line1;
	tchar = *char1;
	*line1 = *line2;
	*char1 = *char2;
	*line2 = tline;
	*char2 = tchar;

	return YES;
}
