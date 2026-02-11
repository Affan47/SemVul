initenv(VOID_A)
{
#if	!MSDOS && defined (FORCEDSTDC)
	char *cp;
	int w;
#endif
	int i;

#if	!MSDOS && defined (FORCEDSTDC)
	if ((w = sizeof(char *) - sizeof(int)) > 0) {
		i = 0x5a;
		cp = (char *)(&i);
		if (*cp == 0x5a) w = 0;
	}
#endif

	for (i = 0; i < ENVLISTSIZ; i++) {
		switch (env_type(i)) {
			case T_CHARP:
			case T_PATH:
			case T_PATHS:
			case T_COLORPAL:
			case T_EDIT:
			case T_KPATHS:
			case T_NOVAR:
				if (envlist[i].var
				&& (*(char **)(envlist[i].var)))
					*((char **)(envlist[i].var)) = NULL;
				break;
#ifdef	PRESETKCODE
			case T_KIN:
			case T_KOUT:
			case T_KNAM:
			case T_KTERM:
				setenv2(env_str(i), PRESETKCODE, 0);

#endif
			default:
#if	!MSDOS && defined (FORCEDSTDC)
				if (w > 0) {
					cp = (char *)&def_num(i);
					memmove(cp, &(cp[w]), sizeof(int));
				}
#endif
				break;
		}
		_evalenv(i);
	}
}
