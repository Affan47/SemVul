ls_fileproc (void *callerdat, struct file_info *finfo)
{
    Vers_TS *vers;
    char *regex_err;
    Node *p, *n;
    bool isdead;
    const char *filename;

    if (regexp_match)
    {
#ifdef FILENAMES_CASE_INSENSITIVE
	  re_set_syntax (REG_ICASE|RE_SYNTAX_EGREP);
#else
	  re_set_syntax (RE_SYNTAX_EGREP);
#endif
	  if ((regex_err = re_comp (regexp_match)) != NULL)
	  {
	      error (1, 0, "bad regular expression passed to 'ls': %s",
                     regex_err);
	  }
	  if (re_exec (finfo->file) == 0)
	      return 0;
    }

    vers = Version_TS (finfo, NULL, show_tag, show_date, 1, 0);


    if (vers->vn_rcs && (!show_dead_revs || long_format))
	isdead = RCS_isdead (finfo->rcs, vers->vn_rcs);
    else
	isdead = false;
    if (!vers->vn_rcs || (!show_dead_revs && isdead))
    {
        freevers_ts (&vers);
	return 0;
    }

    p = findnode (callerdat, finfo->update_dir);
    if (!p)
    {


	filename = finfo->fullname;


	p = findnode (callerdat, ".");
	if (!p)
	{
	    p = getnode ();
	    p->key = xstrdup (".");
	    p->data = getlist ();
	    p->delproc = ls_delproc;
	    addnode (callerdat, p);
	}
    }
    else
	filename = finfo->file;

    n = getnode();
    if (entries_format)
    {
	char *outdate = entries_time (RCS_getrevtime (finfo->rcs, vers->vn_rcs,
                                                      0, 0));
	n->data = Xasprintf ("/%s/%s/%s/%s/%s%s\n",
                             filename, vers->vn_rcs,
                             outdate, vers->options,
                             show_tag ? "T" : "", show_tag ? show_tag : "");
	free (outdate);
    }
    else if (long_format)
    {
	struct long_format_data *out =
		xmalloc (sizeof (struct long_format_data));
	out->header = Xasprintf ("%-5.5s",
                                 vers->options[0] != '\0' ? vers->options
                                                          : "----");

	out->time = gmformat_time_t (RCS_getrevtime (finfo->rcs, vers->vn_rcs,
                                                     0, 0));
	out->footer = Xasprintf (" %-9.9s%s %s%s", vers->vn_rcs,
                                 strlen (vers->vn_rcs) > 9 ? "+" : " ",
                                 show_dead_revs ? (isdead ? "dead " : "     ")
                                                : "",
                                 filename);
	n->data = out;
	n->delproc = long_format_data_delproc;
    }
    else
	n->data = Xasprintf ("%s\n", filename);

    addnode (p->data, n);

    freevers_ts (&vers);
    return 0;
}
