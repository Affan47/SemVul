tag_strnicmp(s1, s2, len)
    char_u	*s1;
    char_u	*s2;
    size_t	len;
{
    int		i;

    while (len > 0)
    {
	i = (int)TOUPPER_ASC(*s1) - (int)TOUPPER_ASC(*s2);
	if (i != 0)
	    return i;
	if (*s1 == NUL)
	    break;
	++s1;
	++s2;
	--len;
    }
    return 0;
}
