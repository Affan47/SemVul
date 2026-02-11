ecpg_strndup(const char *str, size_t len)
{
	size_t		real_len = strlen(str);
	int		use_len = (int) ((real_len > len) ? len : real_len);

	char	   *new = malloc(use_len + 1);

	if (new)
	{
		memcpy(new, str, use_len);
		new[use_len] = '\0';
	}
	else
		errno = ENOMEM;

	return new;
}
