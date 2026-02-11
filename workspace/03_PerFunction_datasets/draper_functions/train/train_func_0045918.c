gethomedir(VOID_A)
{
# ifndef	NOUID
#  ifdef	FD
	uidtable *up;
#  endif
# endif
	CONST char *cp;

	if (!(cp = getconstvar(ENVHOME))) {
# ifndef	NOUID
#  ifdef	FD
		if ((up = finduid(getuid(), NULL))) cp = up -> home;
#  else
		getlogininfo(&cp, NULL);
#  endif
# endif
	}

	return(cp);
}
