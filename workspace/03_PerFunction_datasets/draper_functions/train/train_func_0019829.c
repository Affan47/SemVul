end_of_header (const char *s)
{
    while (s[0] == '\r')
	s++;
    return (s[0] == '\n' && s[1] == '\0');
}
