putsize2(buf, namep, width)
char *buf;
namelist *namep;
int width;
{
	if (isdir(namep))
		VOID_C Xsnprintf(buf, width + 1,
			"%*.*s", width, width, "<DIR>");
#if	MSDOS
	else if (s_isfifo(namep))
		VOID_C Xsnprintf(buf, width + 1,
			"%*.*s", width, width, "<VOL>");
#else
# ifdef	DEP_DOSDRIVE
	else if (dospath2(nullstr) && s_isfifo(namep))
		VOID_C Xsnprintf(buf, width + 1,
			"%*.*s", width, width, "<VOL>");
# endif
	else if (isdev(namep))
		VOID_C Xsnprintf(buf, width + 1,
			"%<*lu,%<*lu",
			width / 2,
			(u_long)major((u_long)(namep -> st_size)),
			width - (width / 2) - 1,
			(u_long)minor((u_long)(namep -> st_size)));
#endif
#if	FD >= 3
	else if (sizeunit)
		VOID_C Xsnprintf(buf, width + 1,
			"%>*qd", width, namep -> st_size);
#endif
	else VOID_C Xsnprintf(buf, width + 1,
		"%<*qd", width, namep -> st_size);

	return(width);
}
