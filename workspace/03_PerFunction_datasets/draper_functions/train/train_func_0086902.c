MakeFilename(char *buffer, char *orig_name, int cnt, int max_chars)
{
	if (cnt == 0 && max_chars == 0)
		strcpy(buffer, orig_name);
	else
		sprintf(buffer, "%s%0*d", orig_name, max_chars, cnt);
}
