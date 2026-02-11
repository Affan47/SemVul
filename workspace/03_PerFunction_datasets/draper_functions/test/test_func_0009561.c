mf_close(mfp, delete)
	MEMFILE	*mfp;
	int		delete;
{
	BHDR		*hp, *nextp;
	NR_TRANS	*tp, *tpnext;
	int			i;

	if (mfp == NULL)
		return;
	if (mfp->mf_fd >= 0)
	{
		if (close(mfp->mf_fd) < 0)
			EMSG("Close error on swap file");
	}
	if (delete && mfp->mf_fname != NULL)
#ifdef KANJI
		remove(fileconvsto(mfp->mf_fname));
#else
		remove((char *)mfp->mf_fname);
#endif

	for (hp = mfp->mf_used_first; hp != NULL; hp = nextp)
	{
		nextp = hp->bh_next;
		mf_free_bhdr(hp);
	}
	while (mfp->mf_free_first != NULL)
		(void)free(mf_rem_free(mfp));
	for (i = 0; i < MEMHASHSIZE; ++i)
		for (tp = mfp->mf_trans[i]; tp != NULL; tp = tpnext)
		{
			tpnext = tp->nt_next;
			free(tp);
		}
	free(mfp->mf_fname);
	free(mfp->mf_xfname);
	free(mfp);
}
