word_length(const char *s)
{
	register int    i = 0;
	while (*(s + i) != ' ' &&
	       *(s + i) != '\t' &&
	       *(s + i) != '\n' &&
	       *(s + i) != '\0')
		i++;
	return i;
}
