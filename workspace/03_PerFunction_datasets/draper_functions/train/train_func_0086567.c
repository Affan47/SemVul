compile_access_log()
{
    char *p;
    const char *fmt = access_log_format;
    size_t len;

    access_log_prog = xdico_list_create();

    while ((p = strchr(fmt, '%'))) {
	char *arg = NULL;
	size_t arglen;
	struct alog_tab *tptr;

	len = p - fmt;
	if (len)
	    add_instr(alog_print, fmt, len);
	p++;
	if (*p == '>' && p[1] == 's') {
	    arg = "1";
	    arglen = 1;
	    p++;
	} else if (*p == '{') {
	    char *q = strchr(p + 1, '}');

	    if (!q) {
		dico_log(L_ERR, 0,
			 _("log format error (near char %d): "
                           "missing terminating `}'"),
			 p - access_log_format);
		add_instr(alog_print, p - 1, 2);
		fmt = p + 1;
		continue;
	    }
	    arglen = q - p - 1;
	    arg = p + 1;
	    p = q + 1;
	}

	tptr = find_alog_entry(*p);
	if (!tptr) {
	    dico_log(L_ERR, 0,
		     _("log format error (near char %d): "
		       "unknown format char `%c'"),
		     p - access_log_format,
		     *p);
	    add_instr(alog_print, fmt, p - fmt + 1);
	} else {
	    if (arg && !tptr->allow_fmt) {
		dico_log(L_ERR, 0,
			 _("log format warning (near char %d): "
			   "format char `%c' does not "
			   "take arguments"),
			 p - access_log_format,
			 *p);
		arg = NULL;
	    }
	    if (tptr->ch == '%') {

		arg = "%";
		arglen = 1;
	    }
	    add_instr(tptr->prt, arg, arglen);
	}
	fmt = p + 1;
    }
    len = strlen(fmt);
    if (len)
	add_instr(alog_print, fmt, len);
}
