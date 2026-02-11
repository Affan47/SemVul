find_cmdline_var(src, usedlen)
    char_u	*src;
    int		*usedlen;
{
    int		len;
    int		i;
    static char *(spec_str[]) = {
		    "%",
#define SPEC_PERC   0
		    "#",
#define SPEC_HASH   1
		    "<cword>",
#define SPEC_CWORD  2
		    "<cWORD>",
#define SPEC_CCWORD 3
		    "<cfile>",
#define SPEC_CFILE  4
		    "<sfile>",
#define SPEC_SFILE  5
#ifdef FEAT_AUTOCMD
		    "<afile>",
# define SPEC_AFILE 6
		    "<abuf>",
# define SPEC_ABUF  7
		    "<amatch>",
# define SPEC_AMATCH 8
#endif
#ifdef FEAT_CLIENTSERVER
		    "<client>"
# define SPEC_CLIENT 9
#endif
    };

    for (i = 0; i < (int)(sizeof(spec_str) / sizeof(char *)); ++i)
    {
	len = (int)STRLEN(spec_str[i]);
	if (STRNCMP(src, spec_str[i], len) == 0)
	{
	    *usedlen = len;
	    return i;
	}
    }
    return -1;
}
