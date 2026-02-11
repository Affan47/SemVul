mf_open(fname, new, fail_nofile)
	char_u	*fname;
	int		new;
	int		fail_nofile;
{
	MEMFILE			*mfp;
	int				i;
	long			size;
#ifdef UNIX
	struct STATFS 	stf;
#endif

	if ((mfp = (MEMFILE *)alloc((unsigned)sizeof(MEMFILE))) == NULL)
	{
		free(fname);
		return NULL;
	}

	if (fname == NULL)
	{
		mfp->mf_fname = NULL;
		mfp->mf_xfname = NULL;
		mfp->mf_fd = -1;
	}
	else
		mf_do_open(mfp, fname, new);


	if (mfp->mf_fd < 0 && fail_nofile)
	{
		free(mfp);
		return NULL;
	}

	mfp->mf_free_first = NULL;
	mfp->mf_used_first = NULL;
	mfp->mf_used_last = NULL;
	mfp->mf_dirty = FALSE;
	mfp->mf_used_count = 0;
	for (i = 0; i < MEMHASHSIZE; ++i)
	{
		mfp->mf_hash[i] = NULL;
		mfp->mf_trans[i] = NULL;
	}
	mfp->mf_page_size = MEMFILE_PAGE_SIZE;

#ifdef UNIX


	if (mfp->mf_fd >= 0 &&
					fstatfs(mfp->mf_fd, &stf, sizeof(struct statfs), 0) == 0 &&
					stf.F_BSIZE >= 1048 && stf.F_BSIZE <= 50000)
		mfp->mf_page_size = stf.F_BSIZE;
#endif

	if (mfp->mf_fd < 0 || new || (size = lseek(mfp->mf_fd, 0L, SEEK_END)) <= 0)
		mfp->mf_blocknr_max = 0;
	else
		mfp->mf_blocknr_max = size / mfp->mf_page_size;
	mfp->mf_blocknr_min = -1;
	mfp->mf_neg_count = 0;
	mfp->mf_infile_count = mfp->mf_blocknr_max;
	if (mfp->mf_fd < 0)
		mfp->mf_used_count_max = 0;
	else
		mfp->mf_used_count_max = p_mm * 1024 / mfp->mf_page_size;

	return mfp;
}
