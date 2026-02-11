adduserfreq(file, frp)
CONST char *file;
freq_t *frp;
{
	lockbuf_t *lck;
	char path[MAXPATHLEN];
	int n, fdin, fdout;

	VOID_C openfreqtbl(NULL, 0);
	if (!(lck = openfreqtbl(file, O_BINARY | O_RDWR))) return(-1);
	Xstrcpy(path, file);
	if ((fdin = lck -> fd) >= 0)
		fdout = opentmpfile(path, 0666 & ~frequmask);
	else {
		VOID_C openfreqtbl(NULL, 0);
		lck = lockopen(path,
			O_BINARY | O_WRONLY | O_CREAT | O_EXCL,
			0666 & ~frequmask);
		fdout = (lck) ? lck -> fd : -1;
	}

	if (fdout < 0) {
		VOID_C openfreqtbl(NULL, 0);
		if (fdin < 0) lockclose(lck);
		return(-1);
	}

	n = copyuserfreq(frp, fdin, fdout);
	if (fdin < 0) {
# if	!MSDOS && !defined (CYGWIN)
		if (n < 0) VOID_C Xunlink(path);
		lockclose(lck);
# else
		lockclose(lck);
		if (n < 0) VOID_C Xunlink(path);
# endif
	}
	else {
# if	!MSDOS && !defined (CYGWIN)
		if (n >= 0) n = Xrename(path, file);
		VOID_C openfreqtbl(NULL, 0);
		VOID_C Xclose(fdout);
# else
		VOID_C openfreqtbl(NULL, 0);
		VOID_C Xclose(fdout);
		if (n >= 0) {
#  if	MSDOS
			n = Xrename(path, file);
#  else
			while ((n = Xrename(path, file)) < 0) {
				if (errno != EACCES) break;
				usleep(100000L);
			}
#  endif
		}
# endif
		if (n < 0) VOID_C Xunlink(path);
	}

	return(n);
}
