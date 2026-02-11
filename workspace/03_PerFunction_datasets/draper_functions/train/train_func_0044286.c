savepathlang(VOID_A)
{
	int i;

	for (i = 0; i < PATHLISTSIZ; i++) VOID_C pathlang(&(pathlist[i]), 1);
# ifndef	_NOSPLITWIN
	for (i = 0; i < MAXWINDOWS; i++) {
#  ifndef	_NOARCHIVE
		archlist[i].path = &(winvar[i].v_archivedir);
		archlist[i].flags = P_STABLE;
		VOID_C pathlang(&(archlist[i]), 1);
#  endif
		fulllist[i].path = &(winvar[i].v_fullpath);
		fulllist[i].flags = P_STABLE;
		VOID_C pathlang(&(fulllist[i]), 1);
	}
# endif
}
