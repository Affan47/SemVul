rtag_delete (RCSNode *rcsfile)
{
    char *version;
    int retcode, isbranch;

    if (numtag)
    {
	version = RCS_getversion (rcsfile, numtag, NULL, 1, NULL);
	if (version == NULL)
	    return (0);
	free (version);
    }

    version = RCS_getversion (rcsfile, symtag, NULL, 1, NULL);
    if (version == NULL)
	return 0;
    free (version);


    isbranch = RCS_nodeisbranch (rcsfile, symtag);
    if ((isbranch && !disturb_branch_tags) ||
	(!isbranch && disturb_branch_tags))
    {
	if (!quiet)
	    error (0, 0,
                   "Not removing %s tag `%s' from `%s'%s.",
                   isbranch ? "branch" : "non-branch",
                   symtag, rcsfile->path,
                   isbranch ? "" : " due to `-B' option");
	return 1;
    }

    if ((retcode = RCS_deltag(rcsfile, symtag)) != 0)
    {
	if (!quiet)
	    error (0, retcode == -1 ? errno : 0,
		   "failed to remove tag `%s' from `%s'", symtag,
		   rcsfile->path);
	return 1;
    }
    RCS_rewrite (rcsfile, NULL, NULL);
    return 0;
}
