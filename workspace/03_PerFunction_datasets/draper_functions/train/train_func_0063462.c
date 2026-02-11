putmode(buf, mode, notype)
char *buf;
u_int mode;
int notype;
{
	int i, c;

	i = 0;
	if (!notype) {
		if (!(c = getfsymbol(mode))) c = '-';
		buf[i++] = c;
	}

	buf[i++] = (mode & S_IRUSR) ? 'r' : '-';
	buf[i++] = (mode & S_IWUSR) ? 'w' : '-';
#if	MSDOS
	buf[i++] = (mode & S_IXUSR) ? 'x' : '-';
	buf[i++] = (mode & S_ISVTX) ? 'a' : '-';
#else
	buf[i++] = (mode & S_ISUID) ? ((mode & S_IXUSR) ? 's' : 'S')
		: ((mode & S_IXUSR) ? 'x' : '-');
	buf[i++] = (mode & S_IRGRP) ? 'r' : '-';
	buf[i++] = (mode & S_IWGRP) ? 'w' : '-';
	buf[i++] = (mode & S_ISGID) ? ((mode & S_IXGRP) ? 's' : 'S')
		: ((mode & S_IXGRP) ? 'x' : '-');
	buf[i++] = (mode & S_IROTH) ? 'r' : '-';
	buf[i++] = (mode & S_IWOTH) ? 'w' : '-';
	buf[i++] = (mode & S_ISVTX) ? ((mode & S_IXOTH) ? 't' : 'T')
		: ((mode & S_IXOTH) ? 'x' : '-');
#endif
	buf[i] = '\0';

	return(i);
}
