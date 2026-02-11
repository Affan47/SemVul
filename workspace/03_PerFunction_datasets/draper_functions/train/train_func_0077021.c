mthca_init_uar_table(struct mthca_dev *dev)
{
	int ret;

	ret = mthca_alloc_init(&dev->uar_table.alloc,
			       dev->limits.num_uars,
			       dev->limits.num_uars - 1,
			       dev->limits.reserved_uars + 1);
	if (ret)
		return ret;

	ret = mthca_init_db_tab(dev);
	if (ret)
		mthca_alloc_cleanup(&dev->uar_table.alloc);

	return ret;
}
