prefix(const char *start, const char *end, const char *test)
{
	if (start == end)
		return (0);

	if (*start++ != *test++)
		return (0);

	while (start < end  &&  *start++ == *test++)
		;

	if (start < end)
		return (0);

	return (1);
}
