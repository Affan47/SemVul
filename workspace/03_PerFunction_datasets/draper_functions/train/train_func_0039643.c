regularize(s)
register char *s;
{
	register char *lp;

	while((lp=index(s, '.')) || (lp=index(s, '/')) || (lp=index(s,' ')))
		*lp = '_';
#if defined(SYSV) && !defined(AIX_31) && !defined(SVR4) && !defined(LINUX) && !defined(__APPLE__)

# ifdef COMPRESS


	{
#  ifdef COMPRESS_EXTENSION
	    int i = 12 - strlen(COMPRESS_EXTENSION);
#  else
	    int i = 10;
#  endif
	    if(strlen(s) > i)
		s[i] = '\0';
	}
# else
	if(strlen(s) > 11)

		s[11] = '\0';
# endif
#endif
}
