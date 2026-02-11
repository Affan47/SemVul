hdestroy(HTAB *hashp)
{
	int i, save_errno;

	save_errno = 0;

#ifdef HASH_STATISTICS
	(void)fprintf(stderr, "hdestroy: accesses %ld collisions %ld\n",
	    hash_accesses, hash_collisions);
	(void)fprintf(stderr, "hdestroy: expansions %ld\n",
	    hash_expansions);
	(void)fprintf(stderr, "hdestroy: overflows %ld\n",
	    hash_overflows);
	(void)fprintf(stderr, "keys %ld maxp %d segmentcount %d\n",
	    hashp->NKEYS, hashp->MAX_BUCKET, hashp->nsegs);

	for (i = 0; i < NCACHED; i++)
		(void)fprintf(stderr,
		    "spares[%d] = %d\n", i, hashp->SPARES[i]);
#endif


	if (__buf_free(hashp, 1, hashp->save_file))
		save_errno = errno;
	if (hashp->dir) {
		free(*hashp->dir);

		while (hashp->exsegs--)
			free(hashp->dir[--hashp->nsegs]);
		free(hashp->dir);
	}
	if (flush_meta(hashp) && !save_errno)
		save_errno = errno;

	for (i = 0; i < hashp->nmaps; i++)
		if (hashp->mapp[i])
			free(hashp->mapp[i]);

	if (hashp->fp != -1)
		(void)close(hashp->fp);

	if(hashp->filename) {
#if defined(_WIN32) || defined(_WINDOWS) || defined(XP_OS2)
		if (hashp->is_temp)
			(void)unlink(hashp->filename);
#endif
		free(hashp->filename);
	}
	if (hashp->tmp_buf)
	    free(hashp->tmp_buf);
	if (hashp->tmp_key)
	    free(hashp->tmp_key);
	free(hashp);
	if (save_errno) {
		errno = save_errno;
		return (DBM_ERROR);
	}
	return (SUCCESS);
}
