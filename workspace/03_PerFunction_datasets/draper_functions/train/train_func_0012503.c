server_write_entries (void)
{
    FILE *f;
    struct an_entry *p;
    struct an_entry *q;

    if (entries == NULL)
	return;

    f = NULL;

    if (!error_pending ())
    {


	f = CVS_FOPEN (CVSADM_ENT, "a");
	if (f == NULL)
	{
	    int save_errno = errno;
	    if (alloc_pending (80 + strlen (CVSADM_ENT)))
		sprintf (pending_error_text, "E cannot open %s", CVSADM_ENT);
	    pending_error = save_errno;
	}
    }
    for (p = entries; p != NULL;)
    {
	if (!error_pending ())
	{
	    if (fprintf (f, "%s\n", p->entry) < 0)
	    {
		int save_errno = errno;
		if (alloc_pending (80 + strlen(CVSADM_ENT)))
		    sprintf (pending_error_text,
			     "E cannot write to %s", CVSADM_ENT);
		pending_error = save_errno;
	    }
	}
	free (p->entry);
	q = p->next;
	free (p);
	p = q;
    }
    entries = NULL;
    if (f != NULL && fclose (f) == EOF && !error_pending ())
    {
	int save_errno = errno;
	if (alloc_pending (80 + strlen (CVSADM_ENT)))
	    sprintf (pending_error_text, "E cannot close %s", CVSADM_ENT);
	pending_error = save_errno;
    }
}
