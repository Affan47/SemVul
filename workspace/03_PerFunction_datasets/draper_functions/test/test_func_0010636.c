fm_lock_state(void)
{
    long	pid;
    int		st;
    FILE	*lockfp;
    int		bkgd = FALSE;

    if ((lockfp = fopen(lockfile, "r")) != NULL)
    {
	int args = fscanf(lockfp, "%ld %d", &pid, &st);
	bkgd = (args == 2);

	if (ferror(lockfp)) {
	    fprintf(stderr, GT_("fetchmail: error reading lockfile \"%s\": %s\n"),
		    lockfile, strerror(errno));
	    fclose(lockfp);
	    exit(PS_EXCLUDE);
	}
	fclose(lockfp);

	if (args == EOF || args == 0 || kill(pid, 0) == -1) {


	    pid = 0;
	    fprintf(stderr,GT_("fetchmail: removing stale lockfile\n"));
	    if (unlink(lockfile)) {
	       if (errno != ENOENT) {
		   perror(lockfile);


		   if (truncate(lockfile, (off_t)0)) {


		       perror(lockfile);
		       exit(PS_EXCLUDE);
		   }
	       }
	    }
	}
    } else {
	pid = 0;
	if (errno != ENOENT) {
	    fprintf(stderr, GT_("fetchmail: error opening lockfile \"%s\": %s\n"),
		    lockfile, strerror(errno));
	    exit(PS_EXCLUDE);
	}
    }

    return(bkgd ? -pid : pid);
}
