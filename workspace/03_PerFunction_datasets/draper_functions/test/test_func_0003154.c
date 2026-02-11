mthca_dealloc_fmr(struct ib_fmr *fmr)
{
	struct mthca_fmr *mfmr = to_mfmr(fmr);
	int err;

	err = mthca_free_fmr(to_mdev(fmr->device), mfmr);
	if (err)
		return err;

	kfree(mfmr);
	return 0;
}
