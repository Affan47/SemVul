fieldread (file, delims, flags, maxf)
    FILE *		file;
    char *		delims;
    int			flags;
    unsigned int	maxf;
    {
    register char *	linebuf;
    int			linemax;
    int			linesize;

    linebuf = (char *) malloc (field_line_inc);
    if (linebuf == NULL)
	return NULL;
    linemax = field_line_inc;
    linesize = 0;


    while (fgets (&linebuf[linesize], linemax - linesize, file)
      != NULL)
	{
	linesize += strlen (&linebuf[linesize]);
	if (linebuf[linesize - 1] == '\n')
	    break;
	else
	    {
	    linemax += field_line_inc;
	    linebuf = (char *) realloc (linebuf, linemax);
	    if (linebuf == NULL)
		return NULL;
	    }
	}
    if (linesize == 0)
	{
	free (linebuf);
	return NULL;
	}
    return fieldmake (linebuf, 1, delims, flags, maxf);
    }
