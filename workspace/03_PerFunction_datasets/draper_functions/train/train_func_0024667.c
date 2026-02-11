get_FL_info(fname, lineno)
char	*fname,
	*lineno;
{
	putmatch(1, fname, (size_t)FILESIZE);
	putmatch(2, lineno, (size_t)FILESIZE);


	if (!jisdigit(lineno[0]) && jisdigit(fname[0])) {
	    putmatch(1, lineno, (size_t)FILESIZE);
	    putmatch(2, fname, (size_t)FILESIZE);
	}
}
