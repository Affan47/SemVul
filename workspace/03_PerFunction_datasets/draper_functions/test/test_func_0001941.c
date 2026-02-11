kill_nojobfiles(void)
{
	int		fd1, fd2;
	unsigned	cnt, errs = 0;
	struct	job_save	*jp;
	struct	spq	inj;
	struct	stat	sbuf;

	for  (cnt = 0;  cnt < HASHMOD;  cnt++)
		for  (jp = hashtab[cnt];  jp;  jp = jp->next)
			if  (jp->in_jfile  &&  !jp->job_path)
				errs++;

	if  (errs == 0  &&  dupjoblist == 0)
		return;

	if  (errs != 0)
		fprintf(stderr, "There are %u job(s) in the job list with no file\n", errs);
	if  (dupjoblist != 0)
		fprintf(stderr, "There are %d job(s) in the job list pointing to the same file\n", errs);

	if  (!Ask("Rewrite job list"))
		return;
	if  ((fd1 = open(JFILE, O_RDONLY)) < 0)
		return;
	if  ((fd2 = open(REBUILDJNAM, O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0)  {
		close(fd1);
		return;
	}

	while  (read(fd1,  (char *) &inj, sizeof(inj)) == sizeof(inj))  {
		if  (!((jp = find_hash(inj.spq_job))  &&  jp->job_path))
			continue;
		if  (jp->in_jfile > 1)
			continue;
		jp->in_jfile = 2;
		write(fd2, (char *) &inj, sizeof(inj));
	}

	fstat(fd1, &sbuf);
#ifdef	HAVE_FCHOWN
	fchown(fd2, sbuf.st_uid, sbuf.st_gid);
#else
	chown(REBUILDJNAM, sbuf.st_uid, sbuf.st_gid);
#endif
	close(fd1);
	close(fd2);

#ifdef	HAVE_RENAME
	rename(REBUILDJNAM, JFILE);
#else
	unlink(JFILE);
	link(REBUILDJNAM, JFILE);
	unlink(REBUILDJNAM);
#endif
}
