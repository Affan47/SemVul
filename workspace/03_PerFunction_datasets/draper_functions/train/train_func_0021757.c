shelltype(const char *shell)
{
	size_t len;

	shell = base_name(shell);
	len = strlen(shell);
	if (len >= 2 && strcmp(shell + len - 2,"sh") == 0)
		return (len >= 3 && shell[len - 3] == 'c');
	return 2;
}
