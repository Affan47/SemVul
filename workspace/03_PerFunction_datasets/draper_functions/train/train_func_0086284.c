anyof(char *s1, char *s2)
{

	while (*s1)
		if (strchr(s2, *s1++))
			return 1;
	return 0;
}
