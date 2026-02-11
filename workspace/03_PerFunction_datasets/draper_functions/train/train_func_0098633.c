mthca_init_srq_table(struct mthca_dev *dev)
{
	int err;

	if (!(dev->mthca_flags & MTHCA_FLAG_SRQ))
		return 0;

	spin_lock_init(&dev->srq_table.lock);

	err = mthca_alloc_init(&dev->srq_table.alloc,
			       dev->limits.num_srqs,
			       dev->limits.num_srqs - 1,
			       dev->limits.reserved_srqs);
	if (err)
		return err;

	err = mthca_array_init(&dev->srq_table.srq,
			       dev->limits.num_srqs);
	if (err)
		mthca_alloc_cleanup(&dev->srq_table.alloc);

	return err;
}
