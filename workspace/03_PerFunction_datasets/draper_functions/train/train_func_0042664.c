mch_get_shellsize()
{
    long	rows = 0;
    long	columns = 0;
    char_u	*p;


# ifdef __EMX__
    {
	int s[2];

	_scrsize(s);
	columns = s[0];
	rows = s[1];
    }
# endif


# ifdef TIOCGWINSZ
    {
	struct winsize	ws;
	int fd = 1;


	if (!isatty(fd) && isatty(read_cmd_fd))
	    fd = read_cmd_fd;
	if (ioctl(fd, TIOCGWINSZ, &ws) == 0)
	{
	    columns = ws.ws_col;
	    rows = ws.ws_row;
	}
    }
# else
#  ifdef TIOCGSIZE
    {
	struct ttysize	ts;
	int fd = 1;


	if (!isatty(fd) && isatty(read_cmd_fd))
	    fd = read_cmd_fd;
	if (ioctl(fd, TIOCGSIZE, &ts) == 0)
	{
	    columns = ts.ts_cols;
	    rows = ts.ts_lines;
	}
    }
#  endif
# endif


    if (columns == 0 || rows == 0 || vim_strchr(p_cpo, CPO_TSIZE) != NULL)
    {
	if ((p = (char_u *)getenv("LINES")))
	    rows = atoi((char *)p);
	if ((p = (char_u *)getenv("COLUMNS")))
	    columns = atoi((char *)p);
    }

#ifdef HAVE_TGETENT


    if (columns == 0 || rows == 0)
	getlinecol(&columns, &rows);
#endif


    if (columns <= 0 || rows <= 0)
	return FAIL;

    Rows = rows;
    Columns = columns;
    limit_screen_size();
    return OK;
}
