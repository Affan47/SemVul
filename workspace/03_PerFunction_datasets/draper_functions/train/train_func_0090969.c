filter_uri_list(char_u **outlist, int max, char_u *src)
{
    int	i, j;

    for (i = j = 0; i < max; ++i)
    {
	outlist[i] = NULL;
	if (STRNCMP(src, "file:", 5) == 0)
	{
	    src += 5;
	    if (STRNCMP(src, "//localhost", 11) == 0)
		src += 11;
	    while (src[0] == '/' && src[1] == '/')
		++src;
	    outlist[j++] = vim_strsave(src);
	}
	src += STRLEN(src) + 1;
    }
    return j;
}
