f_system(argvars, rettv)
    typval_T	*argvars;
    typval_T	*rettv;
{
    char_u	*res = NULL;
    char_u	*p;
    char_u	*infile = NULL;
    char_u	buf[NUMBUFLEN];
    int		err = FALSE;
    FILE	*fd;

    if (check_restricted() || check_secure())
	goto done;

    if (argvars[1].v_type != VAR_UNKNOWN)
    {


	if ((infile = vim_tempname('i')) == NULL)
	{
	    EMSG(_(e_notmp));
	    goto done;
	}

	fd = mch_fopen((char *)infile, WRITEBIN);
	if (fd == NULL)
	{
	    EMSG2(_(e_notopen), infile);
	    goto done;
	}
	p = get_tv_string_buf_chk(&argvars[1], buf);
	if (p == NULL)
	{
	    fclose(fd);
	    goto done;
	}
	if (fwrite(p, STRLEN(p), 1, fd) != 1)
	    err = TRUE;
	if (fclose(fd) != 0)
	    err = TRUE;
	if (err)
	{
	    EMSG(_("E677: Error writing temp file"));
	    goto done;
	}
    }

    res = get_cmd_output(get_tv_string(&argvars[0]), infile,
						 SHELL_SILENT | SHELL_COOKED);

#ifdef USE_CR

    if (res != NULL)
    {
	char_u	*s;

	for (s = res; *s; ++s)
	{
	    if (*s == CAR)
		*s = NL;
	}
    }
#else
# ifdef USE_CRNL

    if (res != NULL)
    {
	char_u	*s, *d;

	d = res;
	for (s = res; *s; ++s)
	{
	    if (s[0] == CAR && s[1] == NL)
		++s;
	    *d++ = *s;
	}
	*d = NUL;
    }
# endif
#endif

done:
    if (infile != NULL)
    {
	mch_remove(infile);
	vim_free(infile);
    }
    rettv->v_type = VAR_STRING;
    rettv->vval.v_string = res;
}
