chomp(char *string)
{
	size_t len;

	if ((len = strlen(string)) > 0 && string[len - 1] == '\n')
		string[len - 1] = '\0';
}
