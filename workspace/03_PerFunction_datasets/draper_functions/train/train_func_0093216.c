getfuncno(ch)
int ch;
{
	int n;

#if	FD >= 3
	if (ch == K_TIMEOUT) return(REREAD_DIR);
#endif

	for (n = 0; n < maxbind; n++)
		if (ch == (int)(bindlist[n].key)) break;
	if (n >= maxbind) return(NO_OPERATION);

#ifndef	_NOPRECEDE
	if (haste && !havestat(&(filelist[filepos]))
	&& (hasdfunc(n) || (funclist[ffunc(n)].status & FN_NEEDSTATUS))
	&& getstatus(&(filelist[filepos])) < 0)
		return(WARNING_BELL);
#endif

	if (hasdfunc(n) && isdir(&(filelist[filepos]))) return(dfunc(n));

	return(ffunc(n));
}
