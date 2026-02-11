lastWhiteSpaceInString(char *s)
{
	char *lastSpace = strrchr(s, ' ');
	char *lastTab = strrchr(s, '\t');
	char *lastWhiteSpace = lastSpace > lastTab ? lastSpace : lastTab;
	return lastWhiteSpace;
}
