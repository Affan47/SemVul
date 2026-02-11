add_tags (RCSNode *rcs, char *vfile, char *vtag, int targc, char **targv)
{
    int i, ierrno;
    Vers_TS *vers;
    int retcode = 0;
    struct file_info finfo;

    if (noexec)
	return 0;

    if ((retcode = RCS_settag (rcs, vtag, vbranch)) != 0)
    {
	ierrno = errno;
	fperrmsg (logfp, 0, retcode == -1 ? ierrno : 0,
		  "ERROR: Failed to set tag %s in %s", vtag, rcs->path);
	error (0, retcode == -1 ? ierrno : 0,
	       "ERROR: Failed to set tag %s in %s", vtag, rcs->path);
	return 1;
    }
    RCS_rewrite (rcs, NULL, NULL);

    memset (&finfo, 0, sizeof finfo);
    finfo.file = vfile;

    finfo.update_dir = NULL;
    finfo.fullname = finfo.file;
    finfo.repository = repository;
    finfo.entries = NULL;
    finfo.rcs = NULL;
    vers = Version_TS (&finfo, NULL, vtag, NULL, 1, 0);
    for (i = 0; i < targc; i++)
    {
	if ((retcode = RCS_settag (rcs, targv[i], vers->vn_rcs)) == 0)
	    RCS_rewrite (rcs, NULL, NULL);
	else
	{
	    ierrno = errno;
	    fperrmsg (logfp, 0, retcode == -1 ? ierrno : 0,
		      "WARNING: Couldn't add tag %s to %s", targv[i],
		      rcs->path);
	    error (0, retcode == -1 ? ierrno : 0,
		   "WARNING: Couldn't add tag %s to %s", targv[i],
		   rcs->path);
	}
    }
    freevers_ts (&vers);
    return 0;
}
