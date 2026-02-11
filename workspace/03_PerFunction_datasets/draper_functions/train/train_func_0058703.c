fieldwrite (file, fieldp, delim)
    FILE *		file;
    register field_t *	fieldp;
    int			delim;
    {
    int			error;
    register unsigned int
			fieldno;

    error = 0;
    for (fieldno = 0;  fieldno < fieldp->nfields;  fieldno++)
	{
	if (fieldno != 0)
	    error |= putc (delim, file) == EOF;
	error |= fputs (fieldp->fields[fieldno], file) == EOF;
	}
    if (fieldp->hadnl)
	error |= putc ('\n', file) == EOF;
    return error;
    }
