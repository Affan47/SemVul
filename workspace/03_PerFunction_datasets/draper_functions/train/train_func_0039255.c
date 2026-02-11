rev_commit_build (rev_commit **commits, rev_commit *leader, int ncommit)
{
    int		n, nfile;
    rev_commit	*commit;
    int		nds;
    rev_dir	**rds;
    rev_file	*first;

    if (ncommit > sfiles) {
	free (files);
	files = 0;
    }
    if (!files)
	files = malloc ((sfiles = ncommit) * sizeof (rev_file *));

    nfile = 0;
    for (n = 0; n < ncommit; n++)
	if (commits[n] && commits[n]->file)
	    files[nfile++] = commits[n]->file;

    if (nfile)
	first = files[0];
    else
	first = NULL;

    rds = rev_pack_files (files, nfile, &nds);

    commit = calloc (1, sizeof (rev_commit) +
		     nds * sizeof (rev_dir *));

    commit->date = leader->date;
    commit->commitid = leader->commitid;
    commit->log = leader->log;
    commit->author = leader->author;

    commit->file = first;
    commit->nfiles = nfile;

    memcpy (commit->dirs, rds, (commit->ndirs = nds) * sizeof (rev_dir *));

    return commit;
}
