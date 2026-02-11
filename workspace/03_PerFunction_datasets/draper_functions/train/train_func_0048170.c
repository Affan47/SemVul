s_strcasecmp(const char *s1, const char *s2)
{
    int i;

    while ((i = (*s1 - *s2)) == 0 && *s1)
    {
	++s1;
	++s2;
    }

    return i;
}
