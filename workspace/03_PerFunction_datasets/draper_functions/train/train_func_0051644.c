Subdirs_Known (List *entries)
{
    struct stickydirtag *sdtp = entries->list->data;


    if (sdtp != NULL && ! sdtp->subdirs)
    {
	FILE *fp;

	sdtp->subdirs = 1;
	if (!noexec)
	{

	    entfilename = CVSADM_ENTLOG;
	    fp = CVS_FOPEN (entfilename, "a");
	    if (fp == NULL)
	    {
		int save_errno = errno;


		if (! isdir (CVSADM))
		    return;
		error (1, save_errno, "cannot open %s", entfilename);
	    }
	    else
	    {
		if (fclose (fp) == EOF)
		    error (1, errno, "cannot close %s", entfilename);
	    }
	}
    }
}
